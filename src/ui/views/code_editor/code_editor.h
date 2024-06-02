#pragma once

#include <kernel/code_editor/code_editor_controller.h>
#include <kernel/code_editor/serialized_graph.h>
#include <misc/Observer.h>
#include <ui/views/code_editor/widget/code_editor_base.h>

namespace dsv::UI {

class CodeEditor : public CodeEditorBase {
    Q_OBJECT
    using SerializedGraph = Kernel::SerializedGraph;
    using TextData = std::optional<SerializedGraph>;
    using ObserverTextData = NSLibrary::CObserver<TextData>;

    using ContentData = std::optional<QString>;
    using ObservableContentData = NSLibrary::CObservableDataMono<ContentData>;
    using ObserverContentData = NSLibrary::CObserver<ContentData>;

public:
    CodeEditor(QWidget *parent = nullptr);
    ObserverTextData *textDataInPort();
    void subscribeToContentData(ObserverContentData *observer);

signals:
    void invalidLinesChanged(const std::vector<size_t> &indexes);

private slots:
    void onTextChanged();

private:
    void onTextData(TextData &&textData);

    ObserverTextData textDataInPort_ = [this](TextData &&textData) { onTextData(std::move(textData)); };
    ObservableContentData contentDataOutPort_;
};

}  // namespace dsv::UI
