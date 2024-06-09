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
};

}  // namespace dsv::UI
