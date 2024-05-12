#include "graph_editor_model_controller.h"

namespace dsv::Kernel {

GraphEditorModelController::GraphEditorModelController(DataModel& dataModel) : dataModel_{dataModel} {}

void GraphEditorModelController::handleDoubleClick() {
    static int counter = 0;
    dataModel_.addNode(counter++, Node{0, ENodeState::INTACT});
}

}  // namespace dsv::Kernel
