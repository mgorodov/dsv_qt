#include "code_editor.h"

namespace dsv::UI {

using SerializedGraph = Kernel::SerializedGraph;
using TextData = std::optional<SerializedGraph>;
using ObserverTextData = NSLibrary::CObserver<TextData>;

namespace {

inline bool isValidLine(const QString &line) {
    if (line.isEmpty()) {
        return true;
    }

    const auto splittedLine = line.split(' ');
    if (splittedLine.size() > 3) {
        return false;
    }

    for (const auto &str : splittedLine) {
        bool ok;
        [[maybe_unused]] auto x = str.toInt(&ok);
        if (!ok) {
            return false;
        }
    }
    return true;
}

}  // namespace

CodeEditor::CodeEditor(QWidget *parent) : CodeEditorBase(parent) {
    setMaximumWidth(300);
    setMinimumWidth(200);
    setPlainText("1, 2\n2, 3\n");
    setPlaceholderText("EXTREMELY\nPARTICULARLY\nHUGE\n&\nJUST\nAWESOME\nCOCK\n\n\\( ͡❛ ͜ʖ ͡❛)/\n    ......\n8=====D");
    connect(this, &CodeEditorBase::textChanged, this, &CodeEditor::onTextChanged);
    connect(this, &CodeEditor::invalidLinesChanged, this, &CodeEditorBase::updateInvalidLines);
}

ObserverTextData *CodeEditor::textDataInPort() {
    return &textDataInPort_;
}

void CodeEditor::subscribeToContentData(ObserverContentData *observer) {
    assert(observer);
    contentDataOutPort_.subscribe(observer);
}

void CodeEditor::onTextChanged() {
    auto text = toPlainText();

    std::vector<size_t> invalidLines;
    const auto contentLines = text.split('\n');
    for (size_t i = 0; i < contentLines.size(); ++i) {
        const auto &line = contentLines[i];
        if (!isValidLine(line)) {
            invalidLines.push_back(i);
        }
    }
    emit invalidLinesChanged(invalidLines);
    if (!invalidLines.empty()) {
        return;
    }

    contentDataOutPort_.set(toPlainText());
}

void CodeEditor::onTextData(TextData &&textData) {
    if (!textData) {
        qDebug() << "No text data yet";
        return;
    }
    qDebug() << "hui pizda blyadina";
    QString text;
    for (const auto &row : textData->rows) {
        text += row.from + "_" + row.to + "_" + row.weight + "\n";
    }
    qDebug() << text;
    setPlainText(text);
}

}  // namespace dsv::UI
