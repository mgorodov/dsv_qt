#pragma once

#include <kernel/code_editor/code_editor_model.h>
#include <kernel/code_editor/code_editor_model_controller.h>
#include <kernel/data_model/data_model.h>
#include <kernel/graph_editor/graph_editor_model.h>
#include <kernel/graph_editor/graph_editor_model_controller.h>
#include <kernel/graph_editor/graph_editor_view_controller.h>

namespace dsv {

class ApplicationKernel {
public:
    ApplicationKernel();

protected:
    Kernel::CodeEditorModel codeEditorModel_;
    Kernel::GraphEditorModel graphEditorModel_;
    Kernel::GraphEditorViewController graphEditorViewController_;

private:
    Kernel::CodeEditorModelController codeEditorModelController_;
    Kernel::GraphEditorModelController graphEditorModelController_;
    Kernel::DataModel dataModel_;
};

}  // namespace dsv
