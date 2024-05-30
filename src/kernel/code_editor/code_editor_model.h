#pragma once
#include <kernel/code_editor/code_editor_model_controller.h>
#include <kernel/code_editor/serialized_graph.h>
#include <kernel/data_model/graph.h>
#include <misc/Observer.h>

namespace dsv::Kernel {

class CodeEditorModel {
    using GraphData = std::optional<Graph>;
    using ObserverGraphData = NSLibrary::CObserver<GraphData>;

    using TextData = std::optional<SerializedGraph>;
    using ObserverTextData = NSLibrary::CObserver<TextData>;
    using ObservableTextData = NSLibrary::CObservable<TextData>;

public:
    CodeEditorModel(CodeEditorModelController& codeEditorModelController);
    ObserverGraphData* graphDataInPort();
    void subscribeToTextData(ObserverTextData* observer);

private:
    void onGraphData(GraphData&& graphData);
    void removeExtraNodes(Graph& graph);
    void removeExtraEdges(Graph& graph);
    void addMissingEdges(Graph& graph);
    void addMissingNodes(Graph& graph);

    ObserverGraphData graphDataInPort_ = [this](GraphData&& graphData) { onGraphData(std::move(graphData)); };
    ObservableTextData textDataOutPort_ = [this]() -> const TextData& { return textData_; };

    CodeEditorModelController& codeEditorModelController_;
    TextData textData_;
};

}  // namespace dsv::Kernel
