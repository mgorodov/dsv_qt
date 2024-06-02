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

    using TextData = std::optional<SerializedGraph>;
    using ObserverTextData = NSLibrary::CObserver<TextData>;
    using ObservableTextData = NSLibrary::CObservable<TextData>;

    using EditData = std::optional<EditAction>;
    using ObserverEditData = NSLibrary::CObserver<EditData>;
    using ObservableEditData = NSLibrary::CObservableDataMono<EditData>;

public:
    CodeEditorModel();
    ObserverGraphData* graphDataInPort();
    void subscribeToTextData(ObserverTextData* observer);
    void subscribeToEditData(ObserverEditData* observer);

private:
    void onGraphData(GraphData&& graphData);
    void addNode();
    void addEdge();
    void removeNode();
    void removeEdge();

    ObserverGraphData graphDataInPort_ = [this](GraphData&& graphData) { onGraphData(std::move(graphData)); };
    ObservableTextData textDataOutPort_ = [this]() -> const TextData& { return textData_; };

    ObservableEditData editDataOutPort_;

    TextData textData_;
};

}  // namespace dsv::Kernel
