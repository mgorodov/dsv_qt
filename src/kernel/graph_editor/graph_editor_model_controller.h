#pragma once

#include <kernel/data_model/data_model.h>

namespace dsv::Kernel {

class GraphEditorModelController {
public:
    GraphEditorModelController(DataModel& dataModel);
    void handleAddingNode();

private:
    DataModel& dataModel_;
};

}  // namespace dsv::Kernel
