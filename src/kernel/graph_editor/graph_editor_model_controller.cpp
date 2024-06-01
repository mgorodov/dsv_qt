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

void GraphEditorModelController::handleAddingNode() {
    static int counter = 0;
    dataModel_->addNode(counter++, Node{0, ENodeState::Intact});
}

ObserverEditData* GraphEditorModelController::editDataInPort() {
    return &editDataInPort_;
}

void GraphEditorModelController::onEditData(EditData&& editData) {
    if (!editData) {
        qDebug() << "No data from code editor model yet";
        return;
    }
    if (editData->object == EObjectType::Node && editData->action == EActionType::Add) {
        handleAddingNode();
    }
}

}  // namespace dsv::Kernel
