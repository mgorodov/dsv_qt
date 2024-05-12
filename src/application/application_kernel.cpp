#include "application_kernel.h"

namespace dsv {

ApplicationKernel::ApplicationKernel()
    : codeEditorModel_{codeEditorModelController_},
      graphEditorModel_{graphEditorModelController_},
      codeEditorModelController_{dataModel_},
      graphEditorModelController_{dataModel_} {
    dataModel_.subscribe(graphEditorModel_.graphDataInPort());
    dataModel_.subscribe(codeEditorModel_.graphDataInPort());
}

}  // namespace dsv
