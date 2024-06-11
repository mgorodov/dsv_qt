#pragma once

#include <kernel/graph_editor/drawable_graph.h>

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>

namespace dsv::UI {

class NodeItem : public QGraphicsItem {
    using DrawableGraph = Kernel::DrawableGraph;

public:
    NodeItem(size_t index, const DrawableGraph::Node &drawableNode);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    size_t index_;
    DrawableGraph::Node drawableNode_;
};

}  // namespace dsv::UI
