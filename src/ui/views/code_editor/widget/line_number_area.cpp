#include "line_number_area.h"

namespace dsv::UI {

LineNumberArea::LineNumberArea(CodeEditorBase *codeEditorBase)
    : QWidget(codeEditorBase), codeEditorBase_(codeEditorBase) {}

QSize LineNumberArea::sizeHint() const {
    return QSize(codeEditorBase_->getLineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event) {
    codeEditorBase_->lineNumberAreaPaintEvent(event);
}

}  // namespace dsv::UI
