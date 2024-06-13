#include "code_editor_model_controller.h"

#include <QDebug>

namespace dsv::Kernel {

using GraphData = std::optional<Graph>;
using ObserverGraphData = NSLibrary::CObserver<GraphData>;

void CodeEditorModelController::connect(DataModel* dataModel) {
    assert(dataModel);
    assert(!dataModel_);
    dataModel_ = dataModel;
    qDebug() << "DataModel connected to CodeEditorModelController";
}

ObserverGraphData* CodeEditorModelController::graphDataInPort() {
    return &graphDataInPort_;
}

void CodeEditorModelController::onGraphData(GraphData&& graphData) {
    if (!graphData) {
        qDebug() << "No data from code editor model yet";
        return;
    }
    if (!dataModel_) {
        qDebug() << "DataModel not connected yet to CodeEditorModelController";
        return;
    }
    dataModel_->reconstructGraph(graphData.value());
    // Find diff with dataModel
}

}  // namespace dsv::Kernel
