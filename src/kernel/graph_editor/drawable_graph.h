#pragma once

#include <QColor>
#include <QPoint>
#include <QString>
#include <unordered_map>

namespace dsv::Kernel {

struct DrawableGraph {
    struct Node {
        QPointF position;
        double radius;
        QString text;
        QColor fill;
        QColor contour;
    };

    struct Edge {
        QPointF from;
        QPointF to;
        double width;
        QString text;
        QColor color;
    };

    std::unordered_map<size_t, Node> nodes;
    std::unordered_map<size_t, std::unordered_map<size_t, Edge>> edges;
};

}  // namespace dsv::Kernel
