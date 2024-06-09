#include "edge_item.h"

namespace dsv::UI {

EdgeItem::EdgeItem(const DrawableGraph::Edge &drawableEdge) : drawableEdge_{drawableEdge} {}

QRectF EdgeItem::boundingRect() const {
    return QRectF(
        drawableEdge_.from.x(), drawableEdge_.from.y(), drawableEdge_.to.x() - drawableEdge_.from.x(),
        drawableEdge_.to.y() - drawableEdge_.from.y()
    );
}

void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen{drawableEdge_.color, drawableEdge_.width});
    painter->drawLine(drawableEdge_.from, drawableEdge_.to);

    painter->setPen(drawableEdge_.textColor);
    painter->drawText(boundingRect(), Qt::AlignCenter, drawableEdge_.text);
}

}  // namespace dsv::UI
