#include "code_editor_model.h"

namespace dsv::Kernel {

CodeEditorModel::CodeEditorModel(CodeEditorModelController& codeEditorModelController)
    : codeEditorModelController_{codeEditorModelController}, textData_{std::in_place_t{}} {}

void CodeEditorModel::onGraphData(GraphData&& graphData) {}

}  // namespace dsv::Kernel
