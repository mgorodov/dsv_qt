#pragma once

#include <QPlainTextEdit>
#include <QWidget>

namespace dsv::UI {

class CodeEditorBase : public QPlainTextEdit {
    Q_OBJECT
public:
    CodeEditorBase(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int getLineNumberAreaWidth() const;

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void updateInvalidLines(const std::vector<size_t> &indexes);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea_;
    std::vector<size_t> invalidLines_;
};

}  // namespace dsv::UI
