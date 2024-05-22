#pragma once

#include <kernel/data_model/graph.h>
#include <kernel/graph_editor/drawable_graph.h>
#include <kernel/graph_editor/graph_editor_model_controller.h>
#include <misc/mouse_action.h>
#include <misc/Observer.h>

namespace dsv::Kernel {

class GraphEditorModel {
    using GraphData = std::optional<Graph>;
    using ObserverGraphData = NSLibrary::CObserver<GraphData>;

    using DrawData = std::optional<DrawableGraph>;
    using ObserverDrawData = NSLibrary::CObserver<DrawData>;
    using ObservableDrawData = NSLibrary::CObservable<DrawData>;

    using MouseData = std::optional<MouseAction>;
    using ObserverMouseData = NSLibrary::CObserver<MouseData>;

public:
    GraphEditorModel(GraphEditorModelController& graphEditorModelController);
    ObserverGraphData* graphDataInPort() {
        return &graphDataInPort_;
    }
    void subscribeToDrawData(ObserverDrawData* observer) {
        assert(observer);
        drawDataOutPort_.subscribe(observer);
    }
    void addNode();

private:
    GraphEditorModelController& graphEditorModelController_;
    DrawData drawData_;

    void onGraphData(GraphData&& graphData);
    ObserverGraphData graphDataInPort_ = [this](GraphData&& graphData) { onGraphData(std::move(graphData)); };

    ObservableDrawData drawDataOutPort_ = [this]() -> const DrawData& { return drawData_; };
};

}  // namespace dsv::Kernel
