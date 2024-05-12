#include "application_kernel.h"

namespace dsv {

ApplicationKernel::ApplicationKernel()
    : graphEditorModel_{graphEditorModelController_}, graphEditorModelController_{dataModel_} {
    dataModel_.subscribe(graphEditorModel_.graphDataInPort());
}

}  // namespace dsv
