#pragma once

#include <kernel/data_model/graph.h>
#include <kernel/graph_editor/drawable_graph.h>
#include <kernel/graph_editor/graph_editor_model_controller.h>
#include <misc/edit_action.h>
#include <misc/mouse_action.h>
#include <misc/Observer.h>
#include <misc/random_gen.h>

namespace dsv::Kernel {

class GraphEditorModel {
    using GraphData = std::optional<Graph>;
    using ObserverGraphData = NSLibrary::CObserver<GraphData>;

    using DrawData = std::optional<DrawableGraph>;
    using ObserverDrawData = NSLibrary::CObserver<DrawData>;
    using ObservableDrawData = NSLibrary::CObservable<DrawData>;

    using MouseData = std::optional<MouseAction>;
    using ObserverMouseData = NSLibrary::CObserver<MouseData>;

    using EditData = std::optional<EditAction>;
    using ObserverEditData = NSLibrary::CObserver<EditData>;
    using ObservableEditData = NSLibrary::CObservableDataMono<EditData>;

public:
    GraphEditorModel();
    ObserverGraphData* graphDataInPort();
    void subscribeToDrawData(ObserverDrawData* observer);
    void subscribeToEditData(ObserverEditData* observer);
    void addNode();
    void addEdge();
    void removeNode();
    void removeEdge();

private:
    void onGraphData(GraphData&& graphData);

    ObserverGraphData graphDataInPort_ = [this](GraphData&& graphData) { onGraphData(std::move(graphData)); };
    ObservableDrawData drawDataOutPort_ = [this]() -> const DrawData& { return drawData_; };
    ObservableEditData editDataOutPort_;

    DrawData drawData_;
    RandomGen rndGen_;
};

}  // namespace dsv::Kernel
