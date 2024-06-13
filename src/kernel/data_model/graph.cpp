#include "graph.h"

#include <vector>

namespace dsv::Kernel {

const std::unordered_map<size_t, Node>& Graph::getNodes() {
    return nodes_;
}

const std::unordered_map<size_t, std::unordered_map<size_t, Edge>>& Graph::getEdges() {
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

}  // namespace dsv::Kernel
