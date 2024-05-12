#pragma once

#include <QString>

namespace dsv::Kernel {

struct SerializedGraph {
    struct Row {
        QString from;
        QString to;
        QString weight;
    };
    std::vector<Row> rows;
};

}  // namespace dsv::Kernel
