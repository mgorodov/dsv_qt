#pragma once

#include <QtGlobal>

namespace dsv {

struct Settings {
    bool weighted = false;
    bool directed = false;
    qreal animationFPS = 0.5;
};

}  // namespace dsv
