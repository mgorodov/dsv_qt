#include "code_editor.h"

namespace dsv::UI {

CodeEditor::CodeEditor(Kernel::CodeEditorController &codeEditorController, QWidget *parent)
    : codeEditorController_(codeEditorController), CodeEditorBase(parent) {
    setMaximumWidth(300);
    setMinimumWidth(200);
    setPlainText("1, 2\n2, 3\n");
    setPlaceholderText("EXTREMELY\nPARTICULARLY\nHUGE\n&\nJUST\nAWESOME\nCOCK\n\n\\( ͡❛ ͜ʖ ͡❛)/\n    ......\n8=====D");
}

void CodeEditor::onTextData(TextData &&textData) {
    if (!textData) {
        qDebug() << "No text data yet";
        return;
    }
    qDebug() << "hui pizda blyadina";
    QString text;
    for (const auto &row : textData->rows) {
        text += row.from + " " + row.to + " " + row.weight + "\n";
    }
    qDebug() << text;
    setPlainText(text);
}

}  // namespace dsv::UI
