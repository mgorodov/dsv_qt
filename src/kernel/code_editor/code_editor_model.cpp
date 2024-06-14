#include "code_editor_model.h"

#include <QDebug>

namespace dsv::Kernel {
using GraphData = std::optional<Graph>;
using ObserverGraphData = NSLibrary::CObserver<GraphData>;

CodeEditorModel::CodeEditorModel() : textData_{std::in_place_t{}}, graphData_{std::in_place_t{}} {}

ObserverGraphData* CodeEditorModel::graphDataInPort() {
    return &graphDataInPort_;
}

void CodeEditorModel::subscribeToTextData(ObserverTextData* observer) {
    assert(observer);
    textDataOutPort_.subscribe(observer);
}

void CodeEditorModel::subscribeToGraphData(ObserverGraphData* observer) {
    assert(observer);
    graphDataOutPort_.subscribe(observer);
}

void CodeEditorModel::onGraphData(GraphData&& graphData) {
    if (!graphData) {
        qDebug() << "No graph data yet for CodeEditorModel";
        return;
    }
    textData_ = SerializedGraph::fromGraph(graphData.value());
    textDataOutPort_.notify();
}

void CodeEditorModel::buildFromString(const QString& str) {
    textData_ = SerializedGraph::fromString(str);
    graphData_ = textData_->toGraph();
    graphDataOutPort_.notify();
}

}  // namespace dsv::Kernel
