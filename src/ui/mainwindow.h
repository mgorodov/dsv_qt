#pragma once

#include <ui/views/code_editor/code_editor.h>
#include <ui/views/graph_editor/graph_editor.h>
#include <ui/widgets/control_panel.h>
#include <ui/widgets/toolbar/toolbar.h>

#include <QWidget>

namespace dsv::UI {

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow();

    GraphEditor* getGraphEditor();
    CodeEditor* getCodeEditor();
    ControlPanel* getControlPanel();

private:
    void createInterface();

    Toolbar toolbar_;
    GraphEditor graphEditor_;
};

}  // namespace dsv::UI
