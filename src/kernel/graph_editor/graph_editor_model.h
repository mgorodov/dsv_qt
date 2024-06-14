#pragma once

#include <kernel/data_model/graph.h>
#include <kernel/graph_editor/drawable_graph.h>
#include <kernel/graph_editor/graph_editor_model_controller.h>
#include <misc/edit_action.h>
#include <misc/mouse_action.h>
#include <misc/Observer.h>
#include <misc/random_gen.h>

#include <list>
#include <QObject>
#include <QTimer>

namespace dsv::Kernel {

class GraphEditorModel : public QObject {
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
    Q_OBJECT
public:
    GraphEditorModel();
    ObserverGraphData* graphDataInPort();
    void subscribeToDrawData(ObserverDrawData* observer);
    void subscribeToEditData(ObserverEditData* observer);
    DrawData* getDrawData();
    void addNode(const QPointF pos);
    void addNodeRandomPos();
    void addEdge(const size_t start, const size_t finish);
    void removeNode(const size_t index);
    void removeEdge(const size_t start, const size_t finish);
    void updateActive();
    void updateValues(GraphData&& graphData);
    void updateColors(GraphData&& graphData);
    void updateNodeText(const size_t index, const QString& text);
    void moveNode(const size_t index, const QPointF pos);
    QColor getColor(EState state);
    void startAlgorithm(size_t index);
    void finishAlgorithm();

private slots:
    void onTimer();

private:
    void onGraphData(GraphData&& graphData);
    size_t getFirstUnusedIndex();

    ObserverGraphData graphDataInPort_ = [this](GraphData&& graphData) { onGraphData(std::move(graphData)); };
    ObservableDrawData drawDataOutPort_ = [this]() -> const DrawData& { return drawData_; };
    ObservableEditData editDataOutPort_;

    std::vector<GraphData> frames_;
    size_t currentFrame_;
    QTimer animationTimer_;

    DrawData drawData_;
    RandomGen rndGen_;
    bool isAlgorithmActive_;
};

}  // namespace dsv::Kernel
