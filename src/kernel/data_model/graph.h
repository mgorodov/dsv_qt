#pragma once

#include <stddef.h>

#include <string>
#include <unordered_map>

namespace dsv::Kernel {

enum class EState { Intact, Selected, Current, Used };

struct Node {
    std::string val;
    EState state{EState::Intact};
    bool operator==(const Node& rhs) const;
};

struct Edge {
    int weight{0};
    EState state{EState::Intact};
    bool operator==(const Edge& rhs) const;
};

class Graph {
public:
    const std::unordered_map<size_t, Node>& getNodes() const;
    const std::unordered_map<size_t, std::unordered_map<size_t, Edge>>& getEdges() const;

    void addNode(size_t index, Node node);
    void removeNode(size_t index);
    void addEdge(size_t from, size_t to, Edge edge);
    void removeEdge(size_t from, size_t to);
    void changeNodeText(size_t index, const std::string& text);
    void changeNodeState(size_t index, EState state);
    void changeEdgeState(size_t from, size_t to, EState state);
    void resetState();

    std::string algorithmOutput;

private:
    //  nodes[i] stores Node with index i
    std::unordered_map<size_t, Node> nodes_;

    // edges[i][j] stores Edge from i to j
    std::unordered_map<size_t, std::unordered_map<size_t, Edge>> edges_;

    // TODO add enum state, currently graph is always directed
};

}  // namespace dsv::Kernel
