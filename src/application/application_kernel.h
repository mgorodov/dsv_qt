#pragma once

#include <kernel/data_model/data_model.h>
#include <kernel/graph_editor/graph_editor_model.h>
#include <kernel/graph_editor/graph_editor_model_controller.h>

namespace dsv {

class ApplicationKernel {
public:
    ApplicationKernel();

protected:
    Kernel::GraphEditorModel graphEditorModel_;

private:
    Kernel::GraphEditorModelController graphEditorModelController_;
    Kernel::DataModel dataModel_;
};
}  // namespace dsv
