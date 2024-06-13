#pragma once

#include <kernel/graph_editor/drawable_graph.h>

#include <QGraphicsItem>
#include <QPainter>

namespace dsv::UI {

class EdgeItem : public QGraphicsItem {
    using DrawableGraph = Kernel::DrawableGraph;

public:
    EdgeItem(const DrawableGraph::Edge &drawableEdge);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    DrawableGraph::Edge drawableEdge_;
    static constexpr qreal m_widthToTextSize = 5;
    static constexpr qreal m_maxTextWidth = 200;
    static constexpr qreal m_textDistFromEdge = 17;
};

}  // namespace dsv::UI
