#include "code_editor_base.h"

#include <ui/views/code_editor/widget/line_number_area.h>

#include <QPainter>
#include <QTextBlock>

namespace dsv::UI {

CodeEditorBase::CodeEditorBase(QWidget *parent) : QPlainTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEditorBase::blockCountChanged, this, &CodeEditorBase::updateLineNumberAreaWidth);
    connect(this, &CodeEditorBase::updateRequest, this, &CodeEditorBase::updateLineNumberArea);
    connect(this, &CodeEditorBase::cursorPositionChanged, this, &CodeEditorBase::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    setTabStopDistance(50);
}

void CodeEditorBase::lineNumberAreaPaintEvent(QPaintEvent *event) {
    QPainter painter(lineNumberArea);
    QFont font = painter.font();
    font.setPixelSize(24);
    painter.setFont(font);
    painter.fillRect(event->rect(), QColor(31, 31, 31));
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            if (blockNumber == textCursor().blockNumber())
                painter.setPen(QColor(150, 150, 150));
            else
                painter.setPen(QColor(110, 118, 129));
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

int CodeEditorBase::getLineNumberAreaWidth() const {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 6 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditorBase::updateLineNumberAreaWidth(int /* newBlockCount */) {
    setViewportMargins(getLineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditorBase::updateLineNumberArea(const QRect &rect, int dy) {
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditorBase::resizeEvent(QResizeEvent *e) {
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), getLineNumberAreaWidth(), cr.height()));
}

void CodeEditorBase::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(255, 255, 255, 20);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

}  // namespace dsv::UI
