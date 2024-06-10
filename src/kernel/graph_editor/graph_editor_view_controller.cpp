#include "graph_editor_view_controller.h"

#include <QDebug>

namespace dsv::Kernel {

using MouseData = std::optional<MouseAction>;
using ObserverMouseData = NSLibrary::CObserver<MouseData>;

using KeyData = std::optional<KeyAction>;
using ObserverKeyData = NSLibrary::CObserver<KeyData>;

void GraphEditorViewController::connect(GraphEditorModel* graphEditorModel) {
    assert(graphEditorModel);
    assert(!graphEditorModel_);
    graphEditorModel_ = graphEditorModel;
    qDebug() << "GraphEditorModel connected to GraphEditorViewController";
}

ObserverMouseData* GraphEditorViewController::mouseDataInPort() {
    return &mouseDataInPort_;
}

ObserverKeyData* GraphEditorViewController::keyDataInPort() {
    return &keyDataInPort_;
}

void GraphEditorViewController::onMouseData(MouseData&& mouseData) {
    if (!mouseData) {
        qDebug() << "No mouse data yet";
        return;
    }
    mousePos_ = mouseData->position;
    if (mouseData->status == EMouseStatus::DoubleClicked) {
        handleAddNodeInRandomPos();
    }

    if (mouseData->status == EMouseStatus::Pressed) {
        handleChangeActive(mouseData->position);
    }

    /*
    qDebug() << "Mouse: " << static_cast<int>(mouseData->status) << ": " << mouseData->position.x() << " "
             << mouseData->position.y();
    */
}

void GraphEditorViewController::onKeyData(KeyData&& keyData) {
    if (!keyData) {
        qDebug() << "No key data yet";
        return;
    }
    if (keyData->status == EKeyStatus::Pressed && keyData->key == Qt::Key_N)
        handleAddNodeInMousePos();

    // qDebug() << "Key: " << static_cast<int>(keyData->status) << ": " << keyData->key;
}

void GraphEditorViewController::handleAddNodeInRandomPos() {
    graphEditorModel_->addNodeRandomPos();
}

void GraphEditorViewController::handleAddNodeInMousePos() {
    if (mousePos_.has_value())
        graphEditorModel_->addNode(mousePos_.value());
    else
        handleAddNodeInRandomPos();
}

std::optional<size_t> GraphEditorViewController::getNodeInPos(const QPointF pos) {
    if (!graphEditorModel_->getDrawData()->has_value()) {
        return std::nullopt;
    }
    DrawableGraph& drawableGraph = graphEditorModel_->getDrawData()->value();

    for (const auto& [index, node] : drawableGraph.nodes) {
        if (pow((pos.x() - node.position.x()), 2) + pow(((pos.y() - 1.5 * 30) - node.position.y()), 2) <= pow(30, 2)) {
            return index;
        }
    }
    return std::nullopt;
}

void GraphEditorViewController::handleChangeActive(const QPointF pos) {
    auto index = getNodeInPos(pos);
    if (index.has_value()) {
        if (!graphEditorModel_->getDrawData()->has_value()) {
            return;
        }
        DrawableGraph& drawableGraph = graphEditorModel_->getDrawData()->value();
        if (drawableGraph.active_nodes.count(index.value())) {
            drawableGraph.active_nodes.erase(index.value());
        } else {
            drawableGraph.active_nodes.insert(index.value());
        }

        graphEditorModel_->updateActive();
    }
}

}  // namespace dsv::Kernel
