#pragma once

#include <kernel/data_model/graph.h>

#include <QString>

namespace dsv::Kernel {

struct SerializedGraph {
    static SerializedGraph fromGraph(const Graph& graph);
    static SerializedGraph fromString(const QString& str);
    Graph toGraph() const;
    QString toString() const;

    struct Row {
        QString from;
        QString to;
        QString weight;

        bool operator==(const Row& rhs) const;
    };
    std::vector<Row> rows;
};

}  // namespace dsv::Kernel
