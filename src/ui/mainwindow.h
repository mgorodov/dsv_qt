#pragma once

#include <ui/views/code_editor/code_editor.h>
#include <ui/views/graph_editor/graph_editor.h>

#include <QWidget>

namespace dsv::UI {

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    GraphEditor* getGraphEditor() {
        return &graphEditor_;
    }
    CodeEditor* getCodeEditor() {
        return &codeEditor_;
    }

private:
    void createInterface();
    CodeEditor codeEditor_;
    GraphEditor graphEditor_;
};

}  // namespace dsv::UI
