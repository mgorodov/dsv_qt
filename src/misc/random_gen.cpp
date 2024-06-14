#include "random_gen.h"

namespace dsv {

int RandomGen::uniformInt(int lower, int upper) {
    std::uniform_int_distribution<> distr(lower, upper);
    return distr(gen);
}

QColor RandomGen::color() {
    std::uniform_int_distribution<> distr(0, 127);
    return QColor::fromRgb(distr(gen), distr(gen), distr(gen));
}

}  // namespace dsv
