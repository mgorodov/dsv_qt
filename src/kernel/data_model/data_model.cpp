#include "data_model.h"

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

}  // namespace dsv::Kernel
