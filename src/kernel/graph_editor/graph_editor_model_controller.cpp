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
    static int counter = 0;
    dataModel_->addNode(index, Node{0, ENodeState::Intact});
}

void GraphEditorModelController::onEditData(EditData&& editData) {
    if (!editData) {
        qDebug() << "No data from code editor model yet";
        return;
    }
    if (editData->object == EObjectType::Node && editData->action == EActionType::Add) {
        handleAddingNode(editData->index);
    }
}

}  // namespace dsv::Kernel
