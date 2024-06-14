#pragma once

#include <kernel/code_editor/code_editor_model.h>

namespace dsv::Kernel {

class CodeEditorController {
    using ContentData = std::optional<QString>;
    using ObserverContentData = NSLibrary::CObserver<ContentData>;

public:
    void connect(CodeEditorModel* codeEditorModel);

    std::vector<size_t> getInvalidLines(const QString& content);
    void updateOnValidCode(const QString& content);

    ObserverContentData* contentDataInPort();

private:
    void onContentData(ContentData&& contentData);

    ObserverContentData contentDataInPort_ = [this](ContentData&& contentData) {
        onContentData(std::move(contentData));
    };
    CodeEditorModel* codeEditorModel_ = nullptr;
};

}  // namespace dsv::Kernel
