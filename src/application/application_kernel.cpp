#include "application_kernel.h"

#include <QDebug>

namespace dsv::Kernel {

ApplicationKernel::ApplicationKernel() {
    codeEditorModelController_.connect(&dataModel_);
    graphEditorModelController_.connect(&dataModel_);

    codeEditorController_.connect(&codeEditorModel_);
    graphEditorViewController_.connect(&graphEditorModel_);

    dataModel_.subscribe(graphEditorModel_.graphDataInPort());
    dataModel_.subscribe(codeEditorModel_.graphDataInPort());
}

CodeEditorModel* ApplicationKernel::getCodeEditorModel() {
    return &codeEditorModel_;
}

CodeEditorModelController* ApplicationKernel::getCodeEditorModelController() {
    return &codeEditorModelController_;
}

CodeEditorController* ApplicationKernel::getCodeEditorController() {
    return &codeEditorController_;
}

GraphEditorModel* ApplicationKernel::getGraphEditorModel() {
    return &graphEditorModel_;
}

GraphEditorModelController* ApplicationKernel::getGraphEditorModelController() {
    return &graphEditorModelController_;
}

GraphEditorViewController* ApplicationKernel::getGraphEditorViewController() {
    return &graphEditorViewController_;
}

}  // namespace dsv::Kernel
