#include "graph_editor_model.h"

#include <QDebug>

namespace dsv::Kernel {
using DrNode = DrawableGraph::Node;

using GraphData = std::optional<Graph>;
using ObserverGraphData = NSLibrary::CObserver<GraphData>;

GraphEditorModel::GraphEditorModel() : drawData_{std::in_place_t{}} {}

ObserverGraphData* GraphEditorModel::graphDataInPort() {
    return &graphDataInPort_;
}

void GraphEditorModel::subscribeToDrawData(ObserverDrawData* observer) {
    assert(observer);
    drawDataOutPort_.subscribe(observer);
}

void GraphEditorModel::subscribeToEditData(ObserverEditData* observer) {
    assert(observer);
    editDataOutPort_.subscribe(observer);
}

void GraphEditorModel::addNode() {
    editDataOutPort_.set(EditAction{EObjectType::Node, EActionType::Add});
}

void GraphEditorModel::addEdge() {
    editDataOutPort_.set(EditAction{EObjectType::Edge, EActionType::Add});
}

void GraphEditorModel::removeNode() {
    editDataOutPort_.set(EditAction{EObjectType::Node, EActionType::Delete});
}

void GraphEditorModel::removeEdge() {
    editDataOutPort_.set(EditAction{EObjectType::Edge, EActionType::Delete});
}

void GraphEditorModel::onGraphData(GraphData&& graphData) {
    if (!graphData) {
        if (drawData_) {
            drawData_.reset();
            drawDataOutPort_.notify();
        }
        return;
    }

    // TODO: Fill drawData_ using some adaptor: GraphData -> DrawableGraph
    DrawableGraph& drawableGraph = drawData_.value();

    for (const auto& [index, node] : drawableGraph.nodes) {
        if (!graphData->getNodes().count(index))
            drawableGraph.nodes.erase(index);
    }

    for (const auto& [index, node] : graphData->getNodes()) {
        if (!drawableGraph.nodes.count(index)) {
            drawableGraph.nodes[index] =
                DrNode{QPointF(rndGen_.getRnd(), rndGen_.getRnd()), 30, "", rndGen_.rndClr(), rndGen_.rndClr()};
        }
    }
    drawDataOutPort_.notify();
}

}  // namespace dsv::Kernel
