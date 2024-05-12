#pragma once

#include <kernel/code_editor/serialized_graph.h>
#include <misc/Observer.h>

#include <QPlainTextEdit>
#include <QWidget>

namespace dsv::UI {

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT
    using TextData = std::optional<Kernel::SerializedGraph>;
    using ObserverTextData = NSLibrary::CObserver<TextData>;

public:
    CodeEditor(QWidget *parent = nullptr);
    ObserverTextData *textDataInPort() {
        return &textDataInPort_;
    }

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int getLineNumberAreaWidth() const;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;

    void onTextData(TextData &&textData);
    ObserverTextData textDataInPort_ = [this](TextData &&textData) { onTextData(std::move(textData)); };
};

class LineNumberArea : public QWidget {
public:
    LineNumberArea(CodeEditor *editor);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    CodeEditor *codeEditor;
};

}  // namespace dsv::UI
