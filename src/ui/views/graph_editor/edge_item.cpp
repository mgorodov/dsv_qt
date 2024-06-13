#include "edge_item.h"

#include <QVector2D>

namespace dsv::UI {

EdgeItem::EdgeItem(const DrawableGraph::Edge &drawableEdge) : drawableEdge_{drawableEdge} {}

QRectF EdgeItem::boundingRect() const {
    return QRectF(
        std::min(drawableEdge_.from.x(), drawableEdge_.to.x()) - m_maxTextWidth / 2,
        std::min(drawableEdge_.from.y(), drawableEdge_.to.y()) - m_maxTextWidth / 2,
        std::abs(drawableEdge_.to.x() - drawableEdge_.from.x()) + m_maxTextWidth,
        std::abs(drawableEdge_.to.y() - drawableEdge_.from.y()) + m_maxTextWidth
    );
}

void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen{drawableEdge_.color, drawableEdge_.width});
    painter->drawLine(drawableEdge_.from, drawableEdge_.to);

    if (drawableEdge_.text != "0") {
        auto perpendicular =
            QVector2D(drawableEdge_.to.y() - drawableEdge_.from.y(), drawableEdge_.from.x() - drawableEdge_.to.x());
        perpendicular.normalize();
        if (perpendicular.y() > 0) {
            perpendicular *= -1;
        }
        const QPointF textPos = boundingRect().center() + perpendicular.toPointF() * m_textDistFromEdge;
        const auto textRect =
            QRectF(textPos.x() - m_maxTextWidth / 2, textPos.y() - m_maxTextWidth / 2, m_maxTextWidth, m_maxTextWidth);

        QFont font;
        font.setPixelSize(drawableEdge_.width * m_widthToTextSize);
        painter->setFont(font);
        painter->setPen(drawableEdge_.textColor);

        painter->drawText(textRect, Qt::AlignCenter, drawableEdge_.text);
    }
}

}  // namespace dsv::UI
