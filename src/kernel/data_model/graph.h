#pragma once

#include <stddef.h>

#include <unordered_map>

namespace dsv::Kernel {

enum class ENodeState { INTACT, SELECTED, USED };
enum class EEdgeState { INTACT, SELECTED, USED };

struct Node {
    int val;
    ENodeState state{ENodeState::INTACT};
};
struct Edge {
    int weight{0};
    EEdgeState state{EEdgeState::INTACT};
};

class Graph {
public:
    void addNode(size_t index, Node node);
    void removeNode(size_t index);
    void addEdge(size_t from, size_t to, Edge edge);
    void removeEdge(size_t from, size_t to);

    //  nodes[i] stores Node with index i
    std::unordered_map<size_t, Node> nodes;

    // edges[i][j] stores Edge from i to j
    std::unordered_map<size_t, std::unordered_map<size_t, Edge>> edges;

    // TODO add bool, currently graph is always directed
};

}  // namespace dsv::Kernel
