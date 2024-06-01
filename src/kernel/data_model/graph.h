#pragma once

#include <stddef.h>

#include <unordered_map>

namespace dsv::Kernel {

enum class ENodeState { Intact, Selected, Used };
enum class EEdgeState { Intact, Selected, Used };

struct Node {
    int val;
    ENodeState state{ENodeState::Intact};
};
struct Edge {
    int weight{0};
    EEdgeState state{EEdgeState::Intact};
};

class Graph {
public:
    const std::unordered_map<size_t, Node>& getNodes();
    const std::unordered_map<size_t, std::unordered_map<size_t, Edge>>& getEdges();

    void addNode(size_t index, Node node);
    void removeNode(size_t index);
    void addEdge(size_t from, size_t to, Edge edge);
    void removeEdge(size_t from, size_t to);

private:
    //  nodes[i] stores Node with index i
    std::unordered_map<size_t, Node> nodes_;

    // edges[i][j] stores Edge from i to j
    std::unordered_map<size_t, std::unordered_map<size_t, Edge>> edges_;

    // TODO add enum state, currently graph is always directed
};

}  // namespace dsv::Kernel
