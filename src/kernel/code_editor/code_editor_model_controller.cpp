#include "code_editor_model_controller.h"

#include <QDebug>

namespace dsv::Kernel {

using EditData = std::optional<EditAction>;
using ObserverEditData = NSLibrary::CObserver<EditData>;

void CodeEditorModelController::connect(DataModel* dataModel) {
    assert(dataModel);
    assert(!dataModel_);
    dataModel_ = dataModel;
    qDebug() << "DataModel connected to CodeEditorModelController";
}

ObserverEditData* CodeEditorModelController::editDataInPort() {
    return &editDataInPort_;
}

void CodeEditorModelController::onEditData(EditData&& editData) {
    if (!editData) {
        qDebug() << "No data from code editor model yet";
        return;
    }
    if (editData->object == EObjectType::Node && editData->action == EActionType::Add) {
        // handleAddnigNode();
    }
}

}  // namespace dsv::Kernel
