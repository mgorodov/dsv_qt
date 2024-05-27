#pragma once

#include <kernel/data_model/graph.h>

#include <QString>

namespace dsv::Kernel {

struct SerializedGraph {
    struct Row {
        QString from;
        QString to;
        QString weight;
        bool operator==(const SerializedGraph::Row& rhs) const;
    };
    std::vector<Row> rows;

    static SerializedGraph fromGraph(const Graph& graph);
    Graph toGraph();

    void migrateTo(const SerializedGraph& newState);
};

}  // namespace dsv::Kernel
