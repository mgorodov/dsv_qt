#pragma once

#include <kernel/code_editor/code_editor_controller.h>
#include <kernel/code_editor/code_editor_model.h>
#include <kernel/code_editor/code_editor_model_controller.h>
#include <kernel/data_model/data_model.h>
#include <kernel/graph_editor/graph_editor_model.h>
#include <kernel/graph_editor/graph_editor_model_controller.h>
#include <kernel/graph_editor/graph_editor_view_controller.h>

namespace dsv::Kernel {

class ApplicationKernel {
public:
    ApplicationKernel();

protected:
    CodeEditorModel* getCodeEditorModel();
    CodeEditorController* getCodeEditorController();

    GraphEditorModel* getGraphEditorModel();
    GraphEditorViewController* getGraphEditorViewController();

private:
    CodeEditorModel codeEditorModel_;
    CodeEditorModelController codeEditorModelController_;
    CodeEditorController codeEditorController_;

    GraphEditorModel graphEditorModel_;
    GraphEditorModelController graphEditorModelController_;
    GraphEditorViewController graphEditorViewController_;

    DataModel dataModel_;
};

}  // namespace dsv::Kernel
