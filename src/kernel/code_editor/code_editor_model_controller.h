#pragma once

#include <kernel/data_model/data_model.h>

namespace dsv::Kernel {

class CodeEditorModelController {
public:
    CodeEditorModelController(DataModel& dataModel);

private:
    DataModel& dataModel_;
};

}  // namespace dsv::Kernel
