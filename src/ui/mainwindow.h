#pragma once

#include <ui/views/graph_editor/grapheditor.h>

#include <QWidget>

namespace dsv::UI {

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    GraphEditor* getGraphEditor() {
        return &graphEditor_;
    }

private:
    void createInterface();
    GraphEditor graphEditor_;
};

}  // namespace dsv::UI
