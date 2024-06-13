#include "data_model.h"

#include <unordered_set>

namespace dsv::Kernel {

DataModel::DataModel() : graph_{std::in_place_t{}} {}

void DataModel::subscribe(ObserverGraphData* observer) {
    assert(observer);
    port_.subscribe(observer);
}

void DataModel::addNode(size_t index, Node node) {
    graph_->addNode(index, node);
    port_.notify();
}

void DataModel::removeNode(size_t index) {
    graph_->removeNode(index);
    port_.notify();
}

void DataModel::addEdge(size_t from, size_t to, Edge edge) {
    graph_->addEdge(from, to, edge);
    port_.notify();
}

void DataModel::removeEdge(size_t from, size_t to) {
    graph_->removeEdge(from, to);
    port_.notify();
}

void DataModel::changeNodeText(size_t index, const QString& text) {
    graph_->changeNodeText(index, text.toStdString());
}

void DataModel::DFS(size_t index) {
    graph_->changeNodeState(index, EState::Selected);
    port_.notify();
    used_.insert(index);
    graph_->changeNodeState(index, EState::Used);
    port_.notify();

    if (!graph_->getEdges().count(index)) {
        return;
    }

    for (auto& [to, edge] : graph_->getEdges().at(index)) {
        graph_->changeEdgeState(index, to, EState::Selected);
        port_.notify();
        graph_->changeEdgeState(index, to, EState::Used);
        port_.notify();

        DFS(to);

        graph_->changeEdgeState(index, to, EState::Selected);
        port_.notify();
        graph_->changeEdgeState(index, to, EState::Used);
        port_.notify();
    }
}

void DataModel::runDFS(size_t index) {
    used_.clear();
    for (auto& [index, node] : graph_->getNodes()) {
        if (!used_.count(index)) {
            DFS(index);
        }
    }
}

void DataModel::reconstructGraph(const Graph& graph) {
    graph_ = graph;
    port_.notify();
}

}  // namespace dsv::Kernel
