#pragma once

#include <QtGlobal>

namespace dsv {

struct Settings {
    bool weighted = false;
    bool directed = false;
    qreal nodeRadius = 30;
    qreal animationFPS = 2;
};

}  // namespace dsv
