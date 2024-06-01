#pragma once

#include <ui/views/code_editor/code_editor.h>
#include <ui/views/graph_editor/graph_editor.h>
#include <ui/widgets/toolbar.h>

#include <QWidget>

namespace dsv::UI {

using CodeEditorController = Kernel::CodeEditorController;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow();

    GraphEditor* getGraphEditor();
    CodeEditor* getCodeEditor();

private:
    void createInterface();

    Toolbar toolbar_;
    // CodeEditor codeEditor_;
    GraphEditor graphEditor_;
};

}  // namespace dsv::UI
