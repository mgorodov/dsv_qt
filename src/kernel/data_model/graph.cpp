#include "graph.h"

namespace dsv::Kernel {

void Graph::addNode(size_t index, Node node) {
    nodes_[index] = node;
}

void Graph::removeNode(size_t index) {
    nodes_.erase(index);
    for (auto& [to, edge] : edges_[index]) {
        edges_[to].erase(index);
        if (edges_[to].empty()) {
            edges_.erase(to);
        }
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

}  // namespace dsv::Kernel
