#pragma once

#include <kernel/data_model/graph.h>

#include <QString>

namespace dsv::Kernel {

struct SerializedGraph {
    static SerializedGraph fromGraph(Graph& graph);
    Graph toGraph();
    void migrateTo(const SerializedGraph& newState);

    struct Row {
        QString from;
        QString to;
        QString weight;
        bool operator==(const SerializedGraph::Row& rhs) const;
    };
    std::vector<Row> rows;
};

}  // namespace dsv::Kernel
