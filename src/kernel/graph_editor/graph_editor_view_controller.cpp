#include "graph_editor_view_controller.h"

#include <QDebug>

namespace dsv::Kernel {

GraphEditorViewController::GraphEditorViewController(GraphEditorModel& graphEditorModel) : graphEditorModel_{graphEditorModel} {}

void GraphEditorViewController::onMouseData(MouseData&& mouseData) {
    if (!mouseData) {
        qDebug() << "No mouse data yet";
        return;
    }
    if (mouseData->status == EMouseStatus::DoubleClicked)
        handleDoubleClick();

    qDebug() << static_cast<int>(mouseData->status) << ": " << mouseData->position.x() << " "
             << mouseData->position.y();
}

void GraphEditorViewController::handleDoubleClick(){
    graphEditorModel_.addNode();
}

}  // namespace dsv::Kernel
