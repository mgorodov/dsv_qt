#pragma once

#include <QPointF>

namespace dsv {

enum class EKeyStatus { Released, Pressed };

struct KeyAction {
    EKeyStatus status;
    Qt::Key key;
};

}  // namespace dsv
