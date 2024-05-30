#include "mainwindow.h"

#include <ui/views/code_editor/code_editor.h>
#include <ui/views/graph_editor/edge.h>
#include <ui/views/graph_editor/graph_editor.h>
#include <ui/views/graph_editor/node.h>
#include <ui/widgets/activitybar.h>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QMenuBar>
#include <QToolBar>

namespace dsv::UI {

MainWindow::MainWindow() {
    setGeometry(160, 90, 1600, 900);
    createInterface();
}

GraphEditor *MainWindow::getGraphEditor() {
    return &graphEditor_;
}

CodeEditor *MainWindow::getCodeEditor() {
    return &codeEditor_;
}

void MainWindow::createInterface() {
    auto *activityBar = new ActivityBar(this);

    auto *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(activityBar, 0, 0);
    mainLayout->addWidget(&codeEditor_, 0, 1);
    mainLayout->addWidget(&graphEditor_, 0, 2);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}

}  // namespace dsv::UI
