#include "graph_editor_model.h"

#include <QDebug>

namespace dsv::Kernel {
using DrawData = std::optional<DrawableGraph>;
using DrNode = DrawableGraph::Node;
using DrEdge = DrawableGraph::Edge;

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
    drawableGraph.nodes[index] =
        DrNode{QPointF(pos.x(), pos.y()), 30, rndGen_.rndClr(), Qt::white, QString::number(index), Qt::white};

    editDataOutPort_.set(EditAction{EObjectType::Node, EActionType::Add, index});
}

void GraphEditorModel::addEdge(const size_t start, const size_t finish) {
    editDataOutPort_.set(EditAction{EObjectType::Edge, EActionType::Add, start, finish});
}

void GraphEditorModel::removeNode(const size_t index) {
    editDataOutPort_.set(EditAction{EObjectType::Node, EActionType::Delete, index});
}

void GraphEditorModel::removeEdge(const size_t start, const size_t finish) {
    editDataOutPort_.set(EditAction{EObjectType::Edge, EActionType::Delete, start, finish});
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

    std::vector<size_t> nodesToDelete;
    for (const auto& [index, node] : drawableGraph.nodes) {
        if (!graphData->getNodes().count(index)) {
            nodesToDelete.emplace_back(index);
        }
    }

    for (const auto& index : nodesToDelete) {
        drawableGraph.nodes.erase(index);
        if (drawableGraph.active_nodes.count(index)) {
            drawableGraph.active_nodes.erase(index);
        }
    }

    for (const auto& [index, node] : graphData->getNodes()) {
        if (!drawableGraph.nodes.count(index)) {
            drawableGraph.nodes[index] = DrNode{QPointF(rndGen_.getRnd(), rndGen_.getRnd()),
                                                30,
                                                rndGen_.rndClr(),
                                                rndGen_.rndClr(),
                                                QString::fromStdString(graphData->getNodes().at(index).val),
                                                Qt::white};
        }
    }

    for (const auto& [from, edges] : graphData->getEdges()) {
        for (const auto& [to, edge] : edges) {
            if (!drawableGraph.edges.count(from) || !drawableGraph.edges.at(from).count(to)) {
                QPointF st = drawableGraph.nodes.at(from).position;
                QPointF en = drawableGraph.nodes.at(to).position;
                drawableGraph.edges[from][to] = DrEdge{st, en, 4, Qt::white, QString::number(graphData->getEdges().at(from).at(to).weight), Qt::white};
            }
        }
    }
    updateActive();
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
            node.contour = node.fill;
        }
    }
    drawDataOutPort_.notify();
}

void GraphEditorModel::updateNodeText(const size_t index, const QString& text) {
    DrawableGraph& drawableGraph = drawData_.value();
    auto& node = drawableGraph.nodes.at(index);
    node.text = text;
    editDataOutPort_.set(EditAction{EObjectType::Node, EActionType::Change, index, index, text});
    drawDataOutPort_.notify();
}

void GraphEditorModel::moveNode(const size_t index, const QPointF pos) {
    DrawableGraph& drawableGraph = drawData_.value();
    auto& node = drawableGraph.nodes.at(index);
    node.position = pos;
    for (auto& [from, edges] : drawableGraph.edges) {
        for (auto& [to, edge] : edges) {
            if (from == index)
                edge.from = pos;
            if (to == index)
                edge.to = pos;
        }
    }
    drawDataOutPort_.notify();
}

}  // namespace dsv::Kernel
