#pragma once

#include <kernel/data_model/data_model.h>

namespace dsv::Kernel {

class GraphEditorModelController {
public:
    void connect(DataModel* dataModel);

    void handleAddingNode();

private:
    DataModel* dataModel_ = nullptr;
};

}  // namespace dsv::Kernel
