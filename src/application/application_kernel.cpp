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

CodeEditorController* ApplicationKernel::getCodeEditorController() {
    return &codeEditorController_;
}

GraphEditorModel* ApplicationKernel::getGraphEditorModel() {
    return &graphEditorModel_;
}

CodeEditorModel* ApplicationKernel::getCodeEditorModel() {
    return &codeEditorModel_;
}

GraphEditorViewController* ApplicationKernel::getGraphEditorViewController() {
    return &graphEditorViewController_;
}

CodeEditorModelController* ApplicationKernel::getCodeEditorModelController() {
    return &codeEditorModelController_;
}

GraphEditorModelController* ApplicationKernel::getGraphEditorModelController() {
    return &graphEditorModelController_;
}

}  // namespace dsv::Kernel
