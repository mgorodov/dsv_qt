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

    if (nodes_.count(id)) {
        scene->removeItem(nodes_[id]);
        delete nodes_[id];
        nodes_.erase(id);
    } else {
        std::cerr << "Node with ID " << id << " does not exist." << std::endl;
        return;
    }


    if (edges_.count(id)) {
        for (auto& [id, edge] : edges_[id]) {
            scene->removeItem(edge);
            delete edge;
        }
        edges_.erase(id);
    }


    for (auto& [source, edges] : edges_) {
        if (edges.count(id)) {
            scene->removeItem(edges_[source][id]);
            delete edges_[source][id];
            edges_[source].erase(id);
        }
    }
}



} // namespace dsv::UI
