#include "random_gen.h"

namespace dsv {

RandomGen::RandomGen() : gen() {}

int RandomGen::getRnd() {
    std::uniform_int_distribution<> distr(50, 800);
    return distr(gen);
}

QColor RandomGen::rndClr() {
    return QColor::fromRgb(getRnd() % 255, getRnd() % 255, getRnd() % 255);
}

}  // namespace dsv
