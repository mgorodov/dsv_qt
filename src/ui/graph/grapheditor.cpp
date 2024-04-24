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
    if (!scene || !cur) return;

    qreal stepSize = 50.0;
    qreal angleIncrement = 30.0;
    qreal currentAngle = 0.0;
    QPointF center = scene->sceneRect().center();

    while (true) {
        qreal dx = stepSize * qCos(qDegreesToRadians(currentAngle));
        qreal dy = stepSize * qSin(qDegreesToRadians(currentAngle));
        QPointF candidatePos = center + QPointF(dx, dy);

        cur->setPos(candidatePos);

        bool isColliding = false;
        QList<QGraphicsItem*> collidingItems = scene->collidingItems(cur);
        for (QGraphicsItem* item : collidingItems) {
            if (item != cur) {
                isColliding = true;
                break;
            }
        }

        if (!isColliding) {
            scene->addItem(cur);
            return;
        }

        currentAngle += angleIncrement;
        if (currentAngle >= 360.0) {
            currentAngle -= 360.0;
            stepSize += 50.0;
        }
    }

    QRectF nodeBoundingRect = cur->boundingRect();
    cur->setPos(scene->sceneRect().topLeft() - QPointF(nodeBoundingRect.width(), nodeBoundingRect.height()));
    scene->addItem(cur);
}

void GraphEditor::AddNode(size_t id)
{
    if (nodes_.find(id) != nodes_.end()) {
        std::cerr << "Node with ID " << id << " already exists." << std::endl;
        return;
    }
    const QString& val = QString::number(id);
    Node* new_node = new Node(val);
    nodes_[id] = new_node;
    PlaceNodeOnEmptySpace(new_node);
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

    if (edges_.count(sourceId)) {
        if (edges_[sourceId][destId]) {
            scene->removeItem(edges_[sourceId][destId]);
            delete edges_[sourceId][destId];
            edges_[sourceId].erase(destId);
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
