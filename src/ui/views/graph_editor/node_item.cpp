#include "node_item.h"

namespace dsv::UI {

using DrawableGraph = Kernel::DrawableGraph;

NodeItem::NodeItem(size_t index, const DrawableGraph::Node &drawableNode)
    : index_{index}, drawableNode_{drawableNode} {}

QRectF NodeItem::boundingRect() const {
    return QRectF(
        drawableNode_.position.x() - drawableNode_.radius, drawableNode_.position.y() - drawableNode_.radius,
        2 * drawableNode_.radius, 2 * drawableNode_.radius
    );
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(drawableNode_.fill);
    painter->setPen(QPen(drawableNode_.contour, m_contourWidth));
    painter->drawEllipse(drawableNode_.position, drawableNode_.radius, drawableNode_.radius);

    QFont font;
    font.setPixelSize(drawableNode_.radius * m_radiusToTextSize);
    painter->setFont(font);
    painter->setPen(drawableNode_.textColor);
    painter->drawText(boundingRect(), Qt::AlignCenter, drawableNode_.text);

    font.setPixelSize(drawableNode_.radius * m_radiusToIndexSize);
    font.setUnderline(true);
    painter->setFont(font);
    painter->setPen(drawableNode_.textColor);
    painter->drawText(boundingRect(), Qt::AlignTop | Qt::AlignHCenter, QString::number(index_));
}

}  // namespace dsv::UI
