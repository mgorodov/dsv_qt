#pragma once

#include <QPointF>

namespace dsv {

enum class EKeyStatus {Pressed, Released};

struct KeyAction {
    EKeyStatus status;
    int key;
};

}  // namespace dsv
