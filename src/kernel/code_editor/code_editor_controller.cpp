#include "code_editor_controller.h"

#include <QDebug>

namespace dsv::Kernel {

using ContentData = std::optional<QString>;
using ObserverContentData = NSLibrary::CObserver<ContentData>;

void CodeEditorController::connect(CodeEditorModel* codeEditorModel) {
    assert(codeEditorModel);
    assert(!codeEditorModel_);
    codeEditorModel_ = codeEditorModel;
    qDebug() << "CodeEditorModel connected to CodeEditorController";
}

ObserverContentData* CodeEditorController::contentDataInPort() {
    return &contentDataInPort_;
}

void CodeEditorController::onContentData(ContentData&& contentData) {
    if (!contentData) {
        qDebug() << "No content data yet for CodeEditorController";
        return;
    }
    qDebug() << "There is content:\n-------" << contentData.value() << "-------";
    // Here call for changes in CodeEditorModel
}

}  // namespace dsv::Kernel
