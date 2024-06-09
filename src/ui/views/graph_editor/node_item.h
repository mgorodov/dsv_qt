#pragma once

#include <kernel/graph_editor/drawable_graph.h>

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>

namespace dsv::UI {

class NodeItem : public QGraphicsItem {
    using DrawableGraph = Kernel::DrawableGraph;

public:
    NodeItem(const DrawableGraph::Node &drawableNode);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    DrawableGraph::Node drawableNode_;
};

}  // namespace dsv::UI
