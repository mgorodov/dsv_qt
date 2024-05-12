#pragma once

#include <QPointF>

namespace dsv {

enum class EMouseStatus { DoubleClicked, Moved, Pressed, Released };

struct MouseAction {
    EMouseStatus status;
    QPointF position;
};

}  // namespace dsv
