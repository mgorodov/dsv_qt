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
    CodeEditorController* getCodeEditorController();
    GraphEditorViewController* getGraphEditorViewController();
    GraphEditorModel* getGraphEditorModel();
    CodeEditorModel* getCodeEditorModel();

private:
    CodeEditorModel codeEditorModel_;
    GraphEditorModel graphEditorModel_;
    CodeEditorController codeEditorController_;
    GraphEditorViewController graphEditorViewController_;

    CodeEditorModelController codeEditorModelController_;
    GraphEditorModelController graphEditorModelController_;
    DataModel dataModel_;
};

}  // namespace dsv::Kernel
