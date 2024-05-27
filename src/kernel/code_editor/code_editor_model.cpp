#include "code_editor_model.h"

#include <QDebug>

namespace dsv::Kernel {

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

void CodeEditorModel::addMissingNodes(const Graph& graph) {
    for (const auto& [index, node] : graph.nodes) {
        SerializedGraph::Row row{.from = QString::number(index)};
        textData_->rows.push_back(std::move(row));
    }
}

void CodeEditorModel::addMissingEdges(const Graph& graph) {
    for (const auto& [from, toEdge] : graph.edges) {
        for (const auto& [to, edge] : toEdge) {
            SerializedGraph::Row row{
                .from = QString::number(from), .to = QString::number(to), .weight = QString::number(edge.weight)
            };
            textData_->rows.push_back(std::move(row));
        }
    }
}

void CodeEditorModel::removeExtraNodes(const Graph& graph) {
    for (const auto& row : textData_->rows) {
    }
    for (const auto& [index, node] : graph.nodes) {
        SerializedGraph::Row row{.from = QString::number(index)};
        textData_->rows.push_back(std::move(row));
    }
}

void CodeEditorModel::removeExtraEdges(const Graph& graph) {}

}  // namespace dsv::Kernel
