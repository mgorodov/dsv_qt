#include "serialized_graph.h"

#include <unordered_set>

namespace dsv::Kernel {

bool SerializedGraph::Row::operator==(const SerializedGraph::Row& rhs) const {
    return from == rhs.from && to == rhs.to && weight == rhs.weight;
}

SerializedGraph SerializedGraph::fromGraph(const Graph& graph) {
    SerializedGraph serializedGraph;

    std::unordered_set<size_t> usedNodes;
    for (const auto& [from, toEdges] : graph.edges) {
        for (const auto& [to, edge] : toEdges) {
            SerializedGraph::Row row{
                .from = QString::number(from), .to = QString::number(to), .weight = QString::number(edge.weight)
            };
            serializedGraph.rows.push_back(std::move(row));
            usedNodes.insert(from);
            usedNodes.insert(to);
        }
    }

    for (const auto& [index, node] : graph.nodes) {
        if (usedNodes.count(index))
            continue;
        SerializedGraph::Row row{.from = QString::number(index)};
        serializedGraph.rows.push_back(std::move(row));
    }

    return serializedGraph;
}

Graph SerializedGraph::toGraph() {
    Graph graph;
    for (const auto& row : rows) {
        if (row.to.isEmpty() && row.weight.isEmpty()) {
            auto index = row.from.toInt();
            graph.nodes[index] = Node{0};
        } else {
            auto from = row.from.toInt();
            auto to = row.to.toInt();
            auto weight = row.weight.toInt();
            graph.edges[from][to] = Edge{weight};
        }
    }
    return graph;
}

void SerializedGraph::migrateTo(const SerializedGraph& newState) {
    std::vector<SerializedGraph::Row> extraRows;
    for (const auto& srcRow : rows) {
        if (std::find(newState.rows.begin(), newState.rows.end(), srcRow) == newState.rows.end()) {
            extraRows.push_back(srcRow);
        }
    }

    std::vector<SerializedGraph::Row> missingRows;
    for (const auto& dstRow : newState.rows) {
        if (std::find(rows.begin(), rows.end(), dstRow) == rows.end()) {
            missingRows.push_back(dstRow);
        }
    }
}

}  // namespace dsv::Kernel
