#include "edge_item.h"

namespace dsv::UI {

EdgeItem::EdgeItem(const DrawableGraph::Edge &drawableEdge) : drawableEdge_{drawableEdge} {}

QRectF EdgeItem::boundingRect() const {
    return QRectF(
        std::min(drawableEdge_.from.x(), drawableEdge_.to.x()) - 100,
        std::min(drawableEdge_.from.y(), drawableEdge_.to.y()) - 100,
        std::abs(drawableEdge_.to.x() - drawableEdge_.from.x()) + 200,
        std::abs(drawableEdge_.to.y() - drawableEdge_.from.y()) + 200
    );
}

void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen{drawableEdge_.color, drawableEdge_.width});
    painter->drawLine(drawableEdge_.from, drawableEdge_.to);

    QFont font;
    font.setPixelSize(drawableEdge_.width * 5);
    painter->setFont(font);
    painter->setPen(drawableEdge_.textColor);
    painter->drawText(boundingRect(), Qt::AlignCenter, drawableEdge_.text);
}

}  // namespace dsv::UI
