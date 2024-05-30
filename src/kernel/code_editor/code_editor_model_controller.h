#pragma once

#include <kernel/data_model/data_model.h>

namespace dsv::Kernel {

class CodeEditorModelController {
public:
    void connect(DataModel* dataModel);

private:
    DataModel* dataModel_ = nullptr;
};

}  // namespace dsv::Kernel
