#pragma once

#include <ui/views/code_editor/widget/code_editor_base.h>

#include <QWidget>

namespace dsv::UI {

class LineNumberArea : public QWidget {
public:
    LineNumberArea(CodeEditorBase *codeEditorBase);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    CodeEditorBase *codeEditorBase_;
};

}  // namespace dsv::UI
