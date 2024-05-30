#include "application_kernel.h"

namespace dsv {

using CodeEditorModel = Kernel::CodeEditorModel;
using GraphEditorModel = Kernel::GraphEditorModel;
using GraphEditorViewController = Kernel::GraphEditorViewController;
using CodeEditorController = Kernel::CodeEditorController;

ApplicationKernel::ApplicationKernel()
    : codeEditorModel_{codeEditorModelController_},
      codeEditorController_{codeEditorModel_},
      codeEditorModelController_{dataModel_},
      graphEditorModel_{graphEditorModelController_},
      graphEditorViewController_{graphEditorModel_},
      graphEditorModelController_{dataModel_} {
    dataModel_.subscribe(graphEditorModel_.graphDataInPort());
    dataModel_.subscribe(codeEditorModel_.graphDataInPort());
}

CodeEditorController* ApplicationKernel::GetCodeEditorController() {
    return &codeEditorController_;
}

GraphEditorModel* ApplicationKernel::GetGraphEditorModel() {
    return &graphEditorModel_;
}

CodeEditorModel* ApplicationKernel::GetCodeEditorModel() {
    return &codeEditorModel_;
}

GraphEditorViewController* ApplicationKernel::GetGraphEditorViewController() {
    return &graphEditorViewController_;
}

}  // namespace dsv
