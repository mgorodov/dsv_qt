#pragma once

#include <kernel/data_model/data_model.h>
#include <kernel/graph_editor/graph_editor_model_controller.h>
#include <misc/mouse_action.h>
#include <misc/Observer.h>

#include <QColor>
#include <QPointF>
#include <unordered_map>

namespace dsv::Kernel {

struct DrawableGraph {
    struct Node {
        QPointF position;
        double radius;
        QString text;
        QColor fill, contour;
    };

    struct Edge {
        QPointF from;
        QPointF to;
        double width;
        QString text;
        QColor color;
    };

    std::unordered_map<size_t, Node> nodes;
    std::unordered_map<size_t, std::unordered_map<size_t, Edge>> edges;
};

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
    ObserverMouseData* mouseDataInPort() {
        return &mouseDataInPort_;
    }
    void subscribeToDrawData(ObserverDrawData* observer) {
        assert(observer);
        drawDataOutPort_.subscribe(observer);
    }

private:
    GraphEditorModelController& graphEditorModelController_;
    DrawData drawData_;
    void onMouseData(MouseData&& mouseData);
    void onKeyData(MouseData&& mouseData);

    void onGraphData(GraphData&& graphData);
    ObserverGraphData graphDataInPort_ = [this](GraphData&& graphData) { onGraphData(std::move(graphData)); };
    ObserverMouseData mouseDataInPort_ = [this](MouseData&& mouseData) { onMouseData(std::move(mouseData)); };

    ObservableDrawData drawDataOutPort_ = [this]() -> const DrawData& { return drawData_; };
};

}  // namespace dsv::Kernel
