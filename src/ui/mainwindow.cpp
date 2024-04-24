#include "mainwindow.h"

#include <ui/widgets/codeeditor.h>
#include <ui/graph/grapheditor.h>

#include <QGridLayout>

#include <ui/graph/edge.h>
#include <ui/graph/node.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>

namespace dsv::UI {

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(160, 90, 1600, 900);
    createInterface();
}

void MainWindow::createInterface()
{
    auto *codeEditor = new CodeEditor(this);
    codeEditor->setMaximumWidth(300);
    codeEditor->setMinimumWidth(200);
    codeEditor->setPlainText("1, 2\n2, 3\n");

    // QGraphicsScene *scene = new QGraphicsScene;
    // QGraphicsView *view = new QGraphicsView(scene);
    // view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);


    // Node *circle1 = new Node("1");
    // Node *circle2 = new Node("2");
    // Node *circle3 = new Node("3");

    // Node *circle1 = new Node();
    // Node *circle2 = new Node();
    // Node *circle3 = new Node();

    // circle1->setPos(100, 50);
    // circle2->setPos(400, 300);
    // circle3->setPos(700, 100);
    // scene->addItem(circle1);
    // scene->addItem(circle2);
    // scene->addItem(circle3);
    // AddEdge(scene, circle1, circle2);
    // AddEdge(scene, circle2, circle3);

    // scene->setSceneRect(0, 0, 1200, 800);

    // view->setRenderHint(QPainter::Antialiasing);
    // //mainLayout->addWidget(view, 0, 1, 1, 100);

    GraphEditor* graphEditor = new GraphEditor(this);

    graphEditor->AddNode(1);
    graphEditor->AddNode(0);
    graphEditor->AddEdge(1, 0);
    graphEditor->AddNode(2);
    graphEditor->AddEdge(2, 0);
    graphEditor->RemoveEdge(1, 0);
    graphEditor->AddEdge(1, 0);

    //graphEditor->AddNode(3);
    graphEditor->RemoveNode(0);

    auto *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(codeEditor, 0, 0);
    mainLayout->addWidget(graphEditor->view, 0, 1);
    setLayout(mainLayout);
}

} // namespace dsv::UI
