#include "edge.h"
#include "node.h"
#include <QPainter>

Edge::Edge(Node* startNode, Node* endNode)
    : QGraphicsLineItem(nullptr), myStartNode(startNode), myEndNode(endNode) {
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::gray, 2));
    setZValue(-1);
    adjust();
}

void Edge::adjust() {
    if (!myStartNode || !myEndNode)
        return;

    QLineF line(mapFromItem(myStartNode, -25, -25), mapFromItem(myEndNode, -25, -25)); //TODO: change 25 to half of radius
    //qreal length = line.length();

    // if (length > naturalLength) {
    //     QPointF edgeOffset((line.dx() * (length - naturalLength) / length),
    //                        (line.dy() * (length - naturalLength) / length));

    //     prepareGeometryChange();
    //     setLine(QLineF(line.p1(), line.p2() - edgeOffset));
    // } else {
        prepareGeometryChange();
        setLine(line);
    //}
}
