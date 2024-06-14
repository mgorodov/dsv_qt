#pragma once

#include <QPointF>

namespace dsv {

using MouseButton = Qt::MouseButton;

enum class EMouseStatus { DoubleClicked, Moved, Pressed, Released };

struct MouseAction {
    EMouseStatus status;
    MouseButton button;
    QPointF position;
};

}  // namespace dsv
