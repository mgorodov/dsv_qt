#pragma once

#include <QColor>
#include <QPoint>
#include <QString>
#include <unordered_map>
#include <unordered_set>

namespace dsv::Kernel {

struct DrawableGraph {
    struct Node {
        QPointF position;
        double radius;
        QColor fill;
        QColor contour;
        QString text;
        QColor textColor;
    };

    struct Edge {
        QPointF from;
        QPointF to;
        double width;
        QColor color;
        QString text;
        QColor textColor;
    };

    struct EdgeEnds {
        size_t start;
        size_t end;
    };

    std::unordered_map<size_t, Node> nodes;
    std::unordered_map<size_t, std::unordered_map<size_t, Edge>> edges;
    std::unordered_set<size_t> active_nodes;
};

}  // namespace dsv::Kernel
