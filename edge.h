#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QObject>

class Node;

class Edge : public QObject, public QGraphicsLineItem {
    Q_OBJECT
public:
    Edge(Node* startNode, Node* endNode);

public slots:
    void adjust();

private:
    Node* myStartNode;
    Node* myEndNode;
    qreal naturalLength = 100.0;
};

#endif // EDGE_H
