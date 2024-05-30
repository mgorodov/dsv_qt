#include "code_editor_model_controller.h"

#include <QDebug>

namespace dsv::Kernel {

void CodeEditorModelController::connect(DataModel* dataModel) {
    assert(dataModel);
    assert(!dataModel_);
    dataModel_ = dataModel;
    qDebug() << "DataModel connected to CodeEditorModelController";
}

}  // namespace dsv::Kernel
