#pragma once
#include <kernel/code_editor/code_editor_controller.h>
#include <kernel/graph_editor/graph_editor_view_controller.h>
#include <ui/mainwindow.h>

namespace dsv::UI {

class ApplicationGUI {
public:
    ApplicationGUI();

protected:
    MainWindow* getMainWindow();
    GraphEditor* getMainGraphEditor();
    CodeEditor* getMainCodeEditor();

private:
    MainWindow mainWindow_;
};

}  // namespace dsv::UI
