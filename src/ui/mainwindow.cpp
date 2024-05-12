#include "mainwindow.h"

#include <ui/views/code_editor/codeeditor.h>
#include <ui/views/graph_editor/edge.h>
#include <ui/views/graph_editor/grapheditor.h>
#include <ui/views/graph_editor/node.h>
#include <ui/widgets/activitybar.h>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QMenuBar>
#include <QToolBar>

namespace dsv::UI {

MainWindow::MainWindow(QWidget *parent) : QWidget{parent}, graphEditor_{this} {
    setGeometry(160, 90, 1600, 900);
    createInterface();
}

void MainWindow::createInterface() {
    auto *codeEditor = new CodeEditor(this);
    codeEditor->setMaximumWidth(300);
    codeEditor->setMinimumWidth(200);
    codeEditor->setPlainText("1, 2\n2, 3\n");
    codeEditor->setPlaceholderText(
        "EXTREMELY\nPARTICULARLY\nHUGE\n&\nJUST\nAWESOME\nCOCK\n\n\\( ͡❛ ͜ʖ ͡❛)/\n    ......\n8=====D");

    auto *activityBar = new ActivityBar(this);

    auto *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(activityBar, 0, 0);
    mainLayout->addWidget(codeEditor, 0, 1);
    mainLayout->addWidget(&graphEditor_, 0, 2);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}

}  // namespace dsv::UI
