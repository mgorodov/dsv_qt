#pragma once
#include <kernel/code_editor/code_editor_model_controller.h>
#include <kernel/code_editor/serialized_graph.h>
#include <kernel/data_model/graph.h>
#include <misc/edit_action.h>
#include <misc/Observer.h>

namespace dsv::Kernel {

class CodeEditorModel {
    using GraphData = std::optional<Graph>;
    using ObserverGraphData = NSLibrary::CObserver<GraphData>;
    using ObservableGraphData = NSLibrary::CObservable<GraphData>;

    using TextData = std::optional<SerializedGraph>;
    using ObserverTextData = NSLibrary::CObserver<TextData>;
    using ObservableTextData = NSLibrary::CObservable<TextData>;

public:
    CodeEditorModel();
    ObserverGraphData* graphDataInPort();
    void subscribeToTextData(ObserverTextData* observer);
    void subscribeToGraphData(ObserverGraphData* observer);

    void buildFromString(const QString& str);

private:
    void onGraphData(GraphData&& graphData);
    void addNode();
    void addEdge();
    void removeNode();
    void removeEdge();

    ObserverGraphData graphDataInPort_ = [this](GraphData&& graphData) { onGraphData(std::move(graphData)); };
    ObservableTextData textDataOutPort_ = [this]() -> const TextData& { return textData_; };
    ObservableGraphData graphDataOutPort_ = [this]() -> const GraphData& { return graphData_; };

    TextData textData_;
    GraphData graphData_;
};

}  // namespace dsv::Kernel
