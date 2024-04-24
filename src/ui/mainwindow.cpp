#include "mainwindow.h"

#include <ui/widgets/codeeditor.h>
#include <ui/graph/grapheditor.h>

#include <QGridLayout>

#include <ui/graph/edge.h>
#include <ui/graph/node.h>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace dsv::UI {

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(160, 90, 1600, 900);
    createInterface();
}

inline void AddEdge(QGraphicsScene *scene, Node *circle1, Node *circle2)
{
    Edge *edge = new Edge(circle1, circle2);
    QObject::connect(circle1, &Node::positionChanged, edge, &Edge::adjust);
    QObject::connect(circle2, &Node::positionChanged, edge, &Edge::adjust);
    scene->addItem(edge);
}

void MainWindow::createInterface()
{
    auto *codeEditor = new CodeEditor(this);
    codeEditor->setMaximumWidth(300);
    codeEditor->setMinimumWidth(200);

    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsView *view = new QGraphicsView(scene);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    Node *circle1 = new Node();
    Node *circle2 = new Node();
    Node *circle3 = new Node();

    circle1->setPos(100, 50);
    circle2->setPos(400, 300);
    circle3->setPos(700, 100);
    scene->addItem(circle1);
    scene->addItem(circle2);
    scene->addItem(circle3);
    AddEdge(scene, circle1, circle2);
    AddEdge(scene, circle2, circle3);

    scene->setSceneRect(0, 0, 1200, 800);

    view->setRenderHint(QPainter::Antialiasing);
    //mainLayout->addWidget(view, 0, 1, 1, 100);

    auto *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(codeEditor, 0, 0);
    mainLayout->addWidget(view, 0, 1);
    setLayout(mainLayout);
}

} // namespace dsv::UI
