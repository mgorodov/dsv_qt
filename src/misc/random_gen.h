#pragma once

#include <QColor>
#include <random>

namespace dsv {

class RandomGen {
public:
    RandomGen() = default;
    int uniformInt(int lower, int upper);
    QColor color();

    std::mt19937 gen{69};
};

}  // namespace dsv
