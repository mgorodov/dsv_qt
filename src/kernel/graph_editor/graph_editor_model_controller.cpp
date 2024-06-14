#include "graph_editor_model_controller.h"

#include <QDebug>

namespace dsv::Kernel {

using EditData = std::optional<EditAction>;
using ObserverEditData = NSLibrary::CObserver<EditData>;

void GraphEditorModelController::connect(DataModel* dataModel) {
    assert(dataModel);
    assert(!dataModel_);
    dataModel_ = dataModel;
    qDebug() << "DataModel connected to GraphEditorModelController";
}

ObserverEditData* GraphEditorModelController::editDataInPort() {
    return &editDataInPort_;
}

void GraphEditorModelController::handleAddingNode(const size_t index) {
    dataModel_->addNode(index, Node{std::to_string(index), EState::Intact});
}

void GraphEditorModelController::handleRemovingNode(const size_t index) {
    dataModel_->removeNode(index);
}

void GraphEditorModelController::handleChangeNodeText(const size_t index, const QString& text) {
    dataModel_->changeNodeText(index, text);
}

void GraphEditorModelController::handleAddingEdge(const size_t indexSt, const size_t indexEnd) {
    dataModel_->addEdge(indexSt, indexEnd, Edge{});
}

void GraphEditorModelController::handleRemovingEdge(const size_t indexSt, const size_t indexEnd) {
    dataModel_->removeEdge(indexSt, indexEnd);
}

void GraphEditorModelController::handleStartAlgorithm(const size_t index) {
    dataModel_->runBFS(index);
}

void GraphEditorModelController::handleFinishAlgorithm() {
    dataModel_->resetState();
}

void GraphEditorModelController::onEditData(EditData&& editData) {
    if (!editData) {
        qDebug() << "No data from code editor model yet";
        return;
    }
    if (editData->object == EObjectType::Node && editData->action == EActionType::Add) {
        handleAddingNode(editData->index);
    }
    if (editData->object == EObjectType::Node && editData->action == EActionType::Delete) {
        handleRemovingNode(editData->index);
    }
    if (editData->object == EObjectType::Edge && editData->action == EActionType::Add) {
        if (editData->indexEnd.has_value())
            handleAddingEdge(editData->index, editData->indexEnd.value());
    }
    if (editData->object == EObjectType::Edge && editData->action == EActionType::Delete) {
        if (editData->indexEnd.has_value())
            handleRemovingEdge(editData->index, editData->indexEnd.value());
    }
    if (editData->object == EObjectType::Node && editData->action == EActionType::Change) {
        if (editData->text.has_value())
            handleChangeNodeText(editData->index, editData->text.value());
    }
    if (editData->object == EObjectType::Algorithm && editData->action == EActionType::DFS) {
        handleStartAlgorithm(editData->index);
    }
    if (editData->object == EObjectType::Algorithm && editData->action == EActionType::Finish) {
        handleFinishAlgorithm();
    }
}

}  // namespace dsv::Kernel
