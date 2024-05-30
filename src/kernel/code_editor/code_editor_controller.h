#pragma once

#include <kernel/code_editor/code_editor_model.h>

namespace dsv::Kernel {

class CodeEditorController {
public:
    void connect(CodeEditorModel* codeEditorModel);

    std::vector<size_t> getInvalidLines(const QString& content);
    void updateOnValidCode(const QString& content);

private:
    CodeEditorModel* codeEditorModel_ = nullptr;
};

}  // namespace dsv::Kernel
