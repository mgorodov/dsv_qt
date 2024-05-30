#include "graph_editor_model_controller.h"

#include <QDebug>

namespace dsv::Kernel {

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

}  // namespace dsv::Kernel
