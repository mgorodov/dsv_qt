#include "graph_editor_model.h"

#include <QDebug>
#include <random>

struct RandomGenTmp {
    RandomGenTmp() : gen(rd()), distr(50, 800) {}
    int getRnd() {
        return distr(gen);
    }
    QColor rndClr() {
        return QColor::fromRgb(getRnd() % 255, getRnd() % 255, getRnd() % 255);
    }
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distr;
};

RandomGenTmp tmpRnd;

namespace dsv::Kernel {
GraphEditorModel::GraphEditorModel(GraphEditorModelController& graphEditorModelController)
    : graphEditorModelController_{graphEditorModelController}, drawData_{std::in_place_t{}} {}

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
        if (!graphData->nodes_.count(index))
            drawableGraph.nodes.erase(index);
    }

    for (const auto& [index, node] : graphData->nodes_) {
        if (!drawableGraph.nodes.count(index)) {
            drawableGraph.nodes[index] = DrawableGraph::Node{QPointF(tmpRnd.getRnd(), tmpRnd.getRnd()), 30, "",
                                                             tmpRnd.rndClr(), tmpRnd.rndClr()};
        }
    }
    drawDataOutPort_.notify();
}

void GraphEditorModel::addNode() {
    // Some animations here

    graphEditorModelController_.handleAddingNode();
}

}  // namespace dsv::Kernel
