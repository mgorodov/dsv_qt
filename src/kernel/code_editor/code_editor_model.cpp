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
    removeExtraNodes(graphData.value());
    removeExtraEdges(graphData.value());
    addMissingEdges(graphData.value());
    addMissingNodes(graphData.value());

    textDataOutPort_.notify();
}

void CodeEditorModel::addMissingNodes(Graph& graph) {
    for (const auto& [index, node] : graph.getNodes()) {
        SerializedGraph::Row row{.from = QString::number(index)};
        textData_->rows.push_back(std::move(row));
    }
}

void CodeEditorModel::addMissingEdges(Graph& graph) {
    for (const auto& [from, toEdge] : graph.getEdges()) {
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
    for (const auto& [index, node] : graph.getNodes()) {
        SerializedGraph::Row row{.from = QString::number(index)};
        textData_->rows.push_back(std::move(row));
    }
}

void CodeEditorModel::removeExtraEdges(Graph& graph) {}

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
