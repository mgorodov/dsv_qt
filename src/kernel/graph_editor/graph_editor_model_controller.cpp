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
    dataModel_->addNode(index, Node{std::to_string(index), ENodeState::Intact});
}

void GraphEditorModelController::handleRemovingNode(const size_t index) {
    dataModel_->removeNode(index);
}

void GraphEditorModelController::handleChangeNodeText(const size_t index, const QString& text) {
    dataModel_->changeNodeText(index, text);
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
    if (editData->object == EObjectType::Node && editData->action == EActionType::Change) {
        if (editData->text.has_value())
            handleChangeNodeText(editData->index, editData->text.value());
    }
}

}  // namespace dsv::Kernel
