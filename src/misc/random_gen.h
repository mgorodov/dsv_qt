#pragma once

#include <QColor>
#include <random>

namespace dsv {

class RandomGen {
public:
    RandomGen();
    int getRnd();
    QColor rndClr();

    std::mt19937 gen;
};

}  // namespace dsv
