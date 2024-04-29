#include "mainwindow.h"

#include <ui/graph/edge.h>
#include <ui/graph/grapheditor.h>
#include <ui/graph/node.h>
#include <ui/widgets/activitybar.h>
#include <ui/widgets/codeeditor.h>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QMenuBar>
#include <QToolBar>

namespace dsv::UI {

MainWindow::MainWindow(QWidget *parent) : QWidget{parent} {
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

    GraphEditor *graphEditor = new GraphEditor(this);
    graphEditor->AddNode(1);
    graphEditor->AddNode(0);
    graphEditor->AddEdge(1, 0);
    graphEditor->AddEdge(0, 1);
    graphEditor->AddNode(2);
    graphEditor->AddEdge(2, 0);
    graphEditor->RemoveEdge(1, 0);
    graphEditor->AddEdge(1, 0);

    // graphEditor->AddNode(3);
    graphEditor->RemoveNode(2);
    graphEditor->AddNode(2);
    graphEditor->AddNode(3);
    graphEditor->AddNode(4);
    graphEditor->AddNode(5);
    graphEditor->AddNode(6);
    graphEditor->AddNode(7);

    auto *activityBar = new ActivityBar(this);

    auto *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(activityBar, 0, 0);
    mainLayout->addWidget(codeEditor, 0, 1);
    mainLayout->addWidget(graphEditor->view, 0, 2);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}

}  // namespace dsv::UI
