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
    ObserverGraphData* graphDataInPort() {
        return &graphDataInPort_;
    }
    void subscribeToTextData(ObserverTextData* observer) {
        assert(observer);
        textDataOutPort_.subscribe(observer);
    }

private:
    CodeEditorModelController& codeEditorModelController_;
    TextData textData_;
    void onGraphData(GraphData&& graphData);
    ObserverGraphData graphDataInPort_ = [this](GraphData&& graphData) { onGraphData(std::move(graphData)); };
    ObservableTextData textDataOutPort_ = [this]() -> const TextData& { return textData_; };
};

}  // namespace dsv::Kernel
