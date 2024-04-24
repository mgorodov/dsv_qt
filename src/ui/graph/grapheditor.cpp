#include "grapheditor.h"
#include <ui/graph/edge.h>
#include <ui/graph/node.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>

namespace dsv::UI {

GraphEditor::GraphEditor(QWidget *parent)
    : QWidget(parent)
{
    scene = new QGraphicsScene;
    view = new QGraphicsView(scene);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    scene->setSceneRect(0, 0, 1200, 800);
    view->setRenderHint(QPainter::Antialiasing);
}

void GraphEditor::PlaceNodeOnEmptySpace(Node* cur)
{
    cur->setPos(100, 50);
}

void GraphEditor::AddNode(size_t id)
{
    if (nodes_.find(id) != nodes_.end()) {
        std::cerr << "Node with ID " << id << " already exists." << std::endl;
        return;
    }
    Node* new_node = new Node();
    nodes_[id] = new_node;
    PlaceNodeOnEmptySpace(new_node);
    scene->addItem(new_node);
}

void GraphEditor::AddEdge(size_t sourceId, size_t destId)
{
    if (nodes_.find(sourceId) == nodes_.end() || nodes_.find(destId) == nodes_.end()) {
        std::cerr << "Both nodes must exist to add an edge." << std::endl;
        return;
    }
    Edge* new_edge = new Edge(nodes_[sourceId], nodes_[destId]);

    QObject::connect(nodes_[sourceId], &Node::positionChanged, new_edge, &Edge::adjust);
    QObject::connect(nodes_[destId], &Node::positionChanged, new_edge, &Edge::adjust);

    edges_[sourceId][destId] = new_edge;
    edges_[destId][sourceId] = new_edge;

    scene->addItem(new_edge);
}

void GraphEditor::RemoveEdge(size_t sourceId, size_t destId) {
    auto sourceIt = edges_.find(sourceId);
    if (sourceIt != edges_.end()) {
        auto& destMap = sourceIt->second;
        auto destIt = destMap.find(destId);

        if (destIt != destMap.end()) {
            scene->removeItem(destIt->second);
            delete destIt->second;
            destMap.erase(destId);
        } else {
            std::cerr << "Edge from " << sourceId << " to " << destId << " does not exist." << std::endl;
        }
    } else {
        std::cerr << "Source node " << sourceId << " does not exist." << std::endl;
    }
}

void GraphEditor::RemoveNode(size_t id) {

    auto nodeIter = nodes_.find(id);
    if (nodeIter != nodes_.end()) {
        scene->removeItem(nodeIter->second);
        delete nodeIter->second;
        nodes_.erase(nodeIter);
    } else {
        std::cerr << "Node with ID " << id << " does not exist." << std::endl;
        return;
    }


    auto edgeIterOut = edges_.find(id);
    if (edgeIterOut != edges_.end()) {
        for (auto& edge : edgeIterOut->second) {
            scene->removeItem(edge.second);
            delete edge.second;
        }
        edges_.erase(edgeIterOut);
    }


    for (auto& pair : edges_) {
        auto& innerMap = pair.second;
        auto edgeIterIn = innerMap.find(id);
        if (edgeIterIn != innerMap.end()) {
            if(edgeIterIn->second) {
                //scene->removeItem(edgeIterIn->second); //!!!!Тут какая-то хуйня, вроде она должна была чекнуть, что мы уже удалил, но нихуя не чекается и пытается удалить пустоту
                //delete edgeIterIn->second;
            }
            innerMap.erase(edgeIterIn);
        }
    }
}



} // namespace dsv::UI
