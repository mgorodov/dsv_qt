#include "graph.h"

#include <vector>

namespace dsv::Kernel {

bool Node::operator==(const Node& rhs) const {
    return val == rhs.val && state == rhs.state;
}

bool Edge::operator==(const Edge& rhs) const {
    return weight == rhs.weight && state == rhs.state;
}

const std::unordered_map<size_t, Node>& Graph::getNodes() const {
    return nodes_;
}

const std::unordered_map<size_t, std::unordered_map<size_t, Edge>>& Graph::getEdges() const {
    return edges_;
}

void Graph::addNode(size_t index, Node node) {
    nodes_.try_emplace(index, std::move(node));
}

void Graph::removeNode(size_t index) {
    nodes_.erase(index);
    std::vector<std::pair<size_t, size_t>> toDel;

    for (auto& [from, edgesTo] : edges_) {
        if (edgesTo.count(index)) {
            toDel.emplace_back(std::make_pair(from, index));
        }
    }

    for (auto& [from, to] : toDel) {
        removeEdge(from, to);
    }

    edges_.erase(index);
}

void Graph::addEdge(size_t from, size_t to, Edge edge) {
    edges_[from][to] = edge;
}

void Graph::removeEdge(size_t from, size_t to) {
    edges_[from].erase(to);
    if (edges_[from].empty()) {
        edges_.erase(from);
    }
}

void Graph::changeNodeText(size_t index, const std::string& text) {
    nodes_.at(index).val = text;
}

void Graph::changeNodeState(size_t index, EState state) {
    if (nodes_.count(index))
        nodes_.at(index).state = state;
}

void Graph::changeEdgeState(size_t from, size_t to, EState state) {
    if (edges_.count(from) && edges_.at(from).count(to))
        edges_.at(from).at(to).state = state;
}

void Graph::resetState() {
    for (auto& [index, node] : nodes_) {
        changeNodeState(index, EState::Intact);
    }

    for (auto& [from, edgesTo] : edges_) {
        for (auto& [to, edge] : edgesTo) {
            changeEdgeState(from, to, EState::Intact);
        }
    }
}

}  // namespace dsv::Kernel
