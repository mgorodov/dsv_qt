#include "code_editor_controller.h"

#include <QDebug>

namespace dsv::Kernel {

void CodeEditorController::connect(CodeEditorModel* codeEditorModel) {
    assert(codeEditorModel);
    assert(!codeEditorModel_);
    codeEditorModel_ = codeEditorModel;
    qDebug() << "CodeEditorModel connected to CodeEditorController";
}

std::vector<size_t> CodeEditorController::getInvalidLines(const QString& content) {
    std::vector<size_t> invalidLines;

    const auto contentLines = content.split('\n');
    for (size_t i = 0; i < contentLines.size(); ++i) {
        const auto& line = contentLines[i];
        const auto splittedLine = line.split(' ');
        if (splittedLine.size() != 3) {
            invalidLines.push_back(i);
            break;
        }
    }
    return invalidLines;
}

void CodeEditorController::updateOnValidCode(const QString& content) {
    const auto contentLines = content.split('\n');
    for (size_t i = 0; i < contentLines.size(); ++i) {
        const auto& line = contentLines[i];
        const auto splittedLine = line.split(' ');
        splittedLine[0].toInt();
    }
}

}  // namespace dsv::Kernel
