#pragma once

#include <kernel/data_model/graph.h>

#include <QString>
#include <unordered_set>

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

    struct RowHash {
        size_t operator()(const Row& row) const;
    };
    std::vector<Row> rows;
    bool operator==(const SerializedGraph& rhs) const;
    bool operator!=(const SerializedGraph& rhs) const;
};

}  // namespace dsv::Kernel
