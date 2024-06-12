#include "graph_editor_view_controller.h"

#include <QDebug>
#include <QInputDialog>
#include <set>

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

    if (mouseData->status == EMouseStatus::Moved) {
        mousePos_ = mouseData->position;
        handleMoveDragableNode(mouseData->position);
    }

    if (mouseData->status == EMouseStatus::DoubleClicked && mouseData->button == Qt::LeftButton) {
        handleChangeLabel(mouseData->position);
    }

    if (mouseData->status == EMouseStatus::Pressed && mouseData->button == Qt::RightButton) {
        handleChangeActive(mouseData->position);
    }

    if (mouseData->status == EMouseStatus::Pressed && mouseData->button == Qt::LeftButton) {
        handleAddDragableNode(mouseData->position);
    }

    if (mouseData->status == EMouseStatus::Released && mouseData->button == Qt::LeftButton) {
        handleRemoveDragableNode(mouseData->position);
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
    if (keyData->status == EKeyStatus::Pressed && keyData->key == Qt::Key_X)
        handleRemoveAllActiveNodes();
    if (keyData->status == EKeyStatus::Pressed && keyData->key == Qt::Key_R)
        handleAddNodeInRandomPos();
    if (keyData->status == EKeyStatus::Pressed && keyData->key == Qt::Key_E)
        handleAddEdges();

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

void GraphEditorViewController::handleRemoveAllActiveNodes() {
    if (!graphEditorModel_->getDrawData()->has_value()) {
        return;
    }
    DrawableGraph& drawableGraph = graphEditorModel_->getDrawData()->value();
    for (const auto& index : drawableGraph.active_nodes) {
        graphEditorModel_->removeNode(index);
    }
}

void GraphEditorViewController::handleChangeLabel(const QPointF pos) {
    auto index = getNodeInPos(pos);
    if (index.has_value()) {
        if (!graphEditorModel_->getDrawData()->has_value()) {
            return;
        }
        DrawableGraph& drawableGraph = graphEditorModel_->getDrawData()->value();
        auto& node = drawableGraph.nodes.at(index.value());
        bool ok;
        QString newText =
            QInputDialog::getText(nullptr, "Edit Node", "Enter new node value", QLineEdit::Normal, node.text, &ok);
        if (ok && !newText.isEmpty()) {
            graphEditorModel_->updateNodeText(index.value(), newText);
        }
    }
}

void GraphEditorViewController::handleAddDragableNode(const QPointF pos) {
    auto index = getNodeInPos(pos);
    if (index.has_value()) {
        DragableNode dragable;
        dragable.index = index.value();
        DrawableGraph& drawableGraph = graphEditorModel_->getDrawData()->value();
        auto& node = drawableGraph.nodes.at(index.value());
        dragable.xDist = node.position.x() - pos.x();
        dragable.yDist = node.position.y() - pos.y();
        dragNode_ = dragable;
    }
}

void GraphEditorViewController::handleRemoveDragableNode(const QPointF pos) {
    if (dragNode_.has_value())
        dragNode_ = std::nullopt;
}
void GraphEditorViewController::handleMoveDragableNode(const QPointF pos) {
    if (dragNode_.has_value()) {
        QPointF position = QPointF(pos.x() + dragNode_.value().xDist, pos.y() + dragNode_.value().yDist);
        graphEditorModel_->moveNode(dragNode_.value().index, position);
    }
}

void GraphEditorViewController::handleAddEdges() {
    if (!graphEditorModel_->getDrawData()->has_value()) {
        return;
    }
    DrawableGraph& drawableGraph = graphEditorModel_->getDrawData()->value();
    if (drawableGraph.active_nodes.size() > 1) {
        std::vector<size_t> indexes(drawableGraph.active_nodes.begin(), drawableGraph.active_nodes.end());
        for (size_t i = 0; i < indexes.size(); ++i) {
            for (size_t j = i + 1; j < indexes.size(); ++j) {
                graphEditorModel_->addEdge(indexes[i], indexes[j]);
            }
        }
    }
}

std::optional<size_t> GraphEditorViewController::getNodeInPos(const QPointF pos) {
    if (!graphEditorModel_->getDrawData()->has_value()) {
        return std::nullopt;
    }
    DrawableGraph& drawableGraph = graphEditorModel_->getDrawData()->value();
    std::set<std::pair<double, size_t>> nodesUnderMouse;
    for (const auto& [index, node] : drawableGraph.nodes) {
        const double dist = pow((pos.x() - node.position.x()), 2) + pow(((pos.y()) - node.position.y()), 2);
        if (dist <= pow(node.radius, 2)) {
            nodesUnderMouse.insert({dist, index});
        }
    }
    if (nodesUnderMouse.size()) {
        return (*nodesUnderMouse.begin()).second;
    }
    return std::nullopt;
}

}  // namespace dsv::Kernel
