#include "code_editor_model.h"

#include <QDebug>

namespace dsv::Kernel {
using GraphData = std::optional<Graph>;
using ObserverGraphData = NSLibrary::CObserver<GraphData>;

CodeEditorModel::CodeEditorModel() : textData_{std::in_place_t{}} {}

ObserverGraphData* CodeEditorModel::graphDataInPort() {
    return &graphDataInPort_;
}

void CodeEditorModel::subscribeToTextData(ObserverTextData* observer) {
    assert(observer);
    textDataOutPort_.subscribe(observer);
}

void CodeEditorModel::subscribeToEditData(ObserverEditData* observer) {
    assert(observer);
    editDataOutPort_.subscribe(observer);
}

void CodeEditorModel::onGraphData(GraphData&& graphData) {
    if (!graphData) {
        qDebug() << "No graph data yet for CodeEditorModel";
        return;
    }
    textData_ = SerializedGraph::fromGraph(graphData.value());
    textDataOutPort_.notify();
}

void CodeEditorModel::addNode() {
    editDataOutPort_.set(EditAction{EObjectType::Node, EActionType::Add});
}

void CodeEditorModel::addEdge() {
    editDataOutPort_.set(EditAction{EObjectType::Edge, EActionType::Add});
}

void CodeEditorModel::removeNode() {
    editDataOutPort_.set(EditAction{EObjectType::Node, EActionType::Delete});
}

void CodeEditorModel::removeEdge() {
    editDataOutPort_.set(EditAction{EObjectType::Edge, EActionType::Delete});
}

}  // namespace dsv::Kernel
