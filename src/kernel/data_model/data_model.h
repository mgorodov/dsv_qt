#pragma once

#include <kernel/data_model/graph.h>
#include <misc/Observer.h>

namespace dsv::Kernel {

class DataModel {
    using GraphData = std::optional<Graph>;
    using ObservableGraphData = NSLibrary::CObservable<GraphData>;
    using ObserverGraphData = NSLibrary::CObserver<GraphData>;

public:
    DataModel();
    void subscribe(ObserverGraphData* observer);

    void addNode(size_t index, Node node);
    void removeNode(size_t index);
    void addEdge(size_t from, size_t to, Edge edge);
    void removeEdge(size_t from, size_t to);
    void changeNodeText(size_t index, const QString& text);

    void reconstructGraph(const Graph& graph);

private:
    GraphData graph_;
    ObservableGraphData port_ = [this]() -> const GraphData& { return graph_; };
};

}  // namespace dsv::Kernel
