#include "application_kernel.h"

namespace dsv {

ApplicationKernel::ApplicationKernel()
    : codeEditorController_{codeEditorModel_},
      codeEditorModel_{codeEditorModelController_},
      codeEditorModelController_{dataModel_},
      graphEditorModel_{graphEditorModelController_},
      graphEditorViewController_{graphEditorModel_},
      graphEditorModelController_{dataModel_} {
    dataModel_.subscribe(graphEditorModel_.graphDataInPort());
    dataModel_.subscribe(codeEditorModel_.graphDataInPort());
}

}  // namespace dsv
