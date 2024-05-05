#pragma once

#include <ui/views/graph_editor/node.h>

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QObject>

namespace dsv::UI {

class Edge : public QObject, public QGraphicsLineItem {
    Q_OBJECT
public:
    Edge(Node *startNode, Node *endNode);

public slots:
    void adjust();

private:
    Node *myStartNode;
    Node *myEndNode;
    qreal naturalLength = 100.0;
};

}  // namespace dsv::UI
