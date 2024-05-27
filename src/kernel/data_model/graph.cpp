#include "graph.h"

namespace dsv::Kernel {

void Graph::addNode(size_t index, Node node) {
    nodes[index] = node;
}

void Graph::removeNode(size_t index) {
    nodes.erase(index);
    for (auto& [to, edge] : edges[index]) {
        edges[to].erase(index);
        if (edges[to].empty()) {
            edges.erase(to);
        }
    }
    edges.erase(index);
}

void Graph::addEdge(size_t from, size_t to, Edge edge) {
    edges[from][to] = edge;
}

void Graph::removeEdge(size_t from, size_t to) {
    edges[from].erase(to);
    if (edges[from].empty()) {
        edges.erase(from);
    }
}

}  // namespace dsv::Kernel
