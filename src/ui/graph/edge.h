#pragma once

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QObject>
#include <ui/graph/node.h>

namespace dsv::UI {

class Edge : public QObject, public QGraphicsLineItem
{
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

} // namespace dsv::UI
