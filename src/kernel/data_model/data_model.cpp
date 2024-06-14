#include "data_model.h"

#include <unistd.h>

#include <queue>
#include <unordered_set>

namespace {
std::string dumpDFSSummary(const std::unordered_set<size_t>& used) {
    std::string summary = "Running DFS\n\nVisited vertixes:\n{";
    bool first = true;
    for (auto i : used) {
        if (!first) {
            summary += ", ";
        }
        summary += std::to_string(i);
        first = false;
    }
    summary += "}\n";
    return summary;
}
}  // namespace

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
    port_.notify();
}

void DataModel::resetState() {
    graph_->resetState();
    port_.notify();
}

void DataModel::DFS(size_t index) {
    graph_->changeNodeState(index, EState::Current);
    port_.notify();

    used_.insert(index);
    graph_->algorithmOutput = dumpDFSSummary(used_);
    graph_->changeNodeState(index, EState::Selected);
    port_.notify();

    if (!graph_->getEdges().count(index)) {
        graph_->changeNodeState(index, EState::Used);
        port_.notify();
        return;
    }

    for (auto& [to, edge] : graph_->getEdges().at(index)) {
        if (!used_.count(to)) {
            graph_->changeEdgeState(index, to, EState::Current);
            port_.notify();
            graph_->changeEdgeState(index, to, EState::Used);

            DFS(to);
        }
    }

    graph_->changeNodeState(index, EState::Current);
    port_.notify();

    graph_->changeNodeState(index, EState::Used);
    port_.notify();
}

void DataModel::runDFS(size_t index) {
    used_.clear();
    DFS(index);
}

void DataModel::runBFS(size_t index) {
    used_.clear();
    std::queue<size_t> q;

    graph_->changeNodeState(index, EState::Current);
    port_.notify();

    q.push(index);
    used_.insert(index);

    graph_->changeNodeState(index, EState::Selected);
    port_.notify();

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        graph_->changeNodeState(cur, EState::Used);
        port_.notify();

        if (!graph_->getEdges().count(cur)) {
            continue;
        }

        for (auto& [to, edge] : graph_->getEdges().at(cur)) {
            if (!used_.count(to)) {
                graph_->changeEdgeState(cur, to, EState::Current);
                port_.notify();
                graph_->changeEdgeState(cur, to, EState::Used);
                graph_->changeNodeState(to, EState::Current);
                port_.notify();

                q.push(to);
                used_.insert(to);

                graph_->changeNodeState(to, EState::Selected);
                port_.notify();
            }
        }
    }
}



void DataModel::reconstructGraph(const Graph& graph) {
    graph_ = graph;
    port_.notify();
}

}  // namespace dsv::Kernel
