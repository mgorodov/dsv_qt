#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <cmath>
#include <QObject>

class Node; // Forward declaration

class Edge : public QObject, public QGraphicsLineItem {
    Q_OBJECT
public:
    Edge(Node* startNode, Node* endNode);

public slots:
    void adjust();

private:
    Node* myStartNode;
    Node* myEndNode;
    qreal naturalLength = 100.0; // Default natural spring length
};

#endif // EDGE_H
