#include "code_editor_model.h"

#include <QDebug>

namespace dsv::Kernel {
using GraphData = std::optional<Graph>;
using ObserverGraphData = NSLibrary::CObserver<GraphData>;

CodeEditorModel::CodeEditorModel(CodeEditorModelController& codeEditorModelController)
    : codeEditorModelController_{codeEditorModelController}, textData_{std::in_place_t{}} {}

void CodeEditorModel::onGraphData(GraphData&& graphData) {
    if (!graphData) {
        qDebug() << "No graph data yet for CodeEditorModel";
        return;
    }
    removeExtraNodes(graphData.value());
    removeExtraEdges(graphData.value());
    addMissingEdges(graphData.value());
    addMissingNodes(graphData.value());

    textDataOutPort_.notify();
}

void CodeEditorModel::addMissingNodes(Graph& graph) {
    for (const auto& [index, node] : graph.GetNodes()) {
        SerializedGraph::Row row{.from = QString::number(index)};
        textData_->rows.push_back(std::move(row));
    }
}

void CodeEditorModel::addMissingEdges(Graph& graph) {
    for (const auto& [from, toEdge] : graph.GetEdges()) {
        for (const auto& [to, edge] : toEdge) {
            SerializedGraph::Row row{
                .from = QString::number(from), .to = QString::number(to), .weight = QString::number(edge.weight)
            };
            textData_->rows.push_back(std::move(row));
        }
    }
}

void CodeEditorModel::removeExtraNodes(Graph& graph) {
    for (const auto& row : textData_->rows) {
    }
    for (const auto& [index, node] : graph.GetNodes()) {
        SerializedGraph::Row row{.from = QString::number(index)};
        textData_->rows.push_back(std::move(row));
    }
}

void CodeEditorModel::removeExtraEdges(Graph& graph) {}

ObserverGraphData* CodeEditorModel::graphDataInPort() {
    return &graphDataInPort_;
}

void CodeEditorModel::subscribeToTextData(ObserverTextData* observer) {
    assert(observer);
    textDataOutPort_.subscribe(observer);
}

}  // namespace dsv::Kernel
