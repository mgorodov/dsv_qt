#include "graph_editor_model.h"

#include <QDebug>

namespace dsv::Kernel {
using DrawData = std::optional<DrawableGraph>;
using DrNode = DrawableGraph::Node;

using GraphData = std::optional<Graph>;
using ObserverGraphData = NSLibrary::CObserver<GraphData>;

GraphEditorModel::GraphEditorModel() : drawData_{std::in_place} {}

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

DrawData* GraphEditorModel::getDrawData() {
    return &drawData_;
}

void GraphEditorModel::addNodeRandomPos() {
    editDataOutPort_.set(EditAction{EObjectType::Node, EActionType::Add, getFirstUnusedIndex()});
}

void GraphEditorModel::addNode(const QPointF pos) {
    DrawableGraph& drawableGraph = drawData_.value();
    const auto index = getFirstUnusedIndex();
    drawableGraph.nodes[index] = DrNode{
        QPointF(pos.x(), pos.y() - (1.5 * 30)), 30, rndGen_.rndClr(), Qt::white, QString::number(index), Qt::white
    };

    editDataOutPort_.set(EditAction{EObjectType::Node, EActionType::Add, index});
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
            drawableGraph.nodes[index] = DrNode{QPointF(rndGen_.getRnd(), rndGen_.getRnd()),
                                                30,
                                                rndGen_.rndClr(),
                                                Qt::white,
                                                QString::number(index),
                                                Qt::white};
        }
    }
    drawDataOutPort_.notify();
}

size_t GraphEditorModel::getFirstUnusedIndex() {
    size_t ind = 0;
    DrawableGraph& drawableGraph = drawData_.value();
    for (; ind < drawableGraph.nodes.size(); ++ind) {
        if (!drawableGraph.nodes.count(ind)) {
            return ind;
        }
    }
    return ind;
}

void GraphEditorModel::updateActive() {
    DrawableGraph& drawableGraph = drawData_.value();
    for (auto& [index, node] : drawableGraph.nodes) {
        if (drawableGraph.active_nodes.count(index)) {
            node.contour = Qt::red;
        } else {
            node.contour = Qt::white;
        }
    }
    drawDataOutPort_.notify();
}

}  // namespace dsv::Kernel
