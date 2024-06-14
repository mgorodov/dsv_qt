#pragma once

#include <QColor>
#include <QtGlobal>

struct Settings {
    /* Graph rendering */
    qreal nodeSize = 10;
    qreal edgeWidth = 10;
    QColor nodeFillColor = QColor{Qt::black};
    QColor nodeContourColor = QColor{Qt::white};
    QColor edgeColor = QColor{Qt::black};

    bool randomNodeFillColor = false;
    bool randomNodeContourColor = false;
    bool randomEdgeColor = false;

    /* Graph properties */
    bool isDirected = false;
    bool isWeighted = false;

    /* TODO: add dynamic settings */
};
