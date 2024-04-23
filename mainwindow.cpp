#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "node.h"
#include "edge.h"
#include <QLayout>
#include <QGraphicsView>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(scene, this);

    //auto* CircleWidget = new Node(this);
    Node* circle1 = new Node();
    Node* circle2 = new Node();
    Node* circle3 = new Node();

    //Edge* edge = new Edge(circle1, circle2);


    //QObject::connect(circle1, &Node::positionChanged, edge, &Edge::adjust);
    //QObject::connect(circle2, &Node::positionChanged, edge, &Edge::adjust);

    scene->addItem(circle1);
    circle2->setPos(100, 100);
    scene->addItem(circle2);
    circle3->setPos(200, 200);
    scene->addItem(circle3);

    MainWindow::AddEdge(scene, circle1, circle2);
    MainWindow::AddEdge(scene, circle2, circle3);

    scene->setSceneRect(-200, -200, 1000, 800);

    view->setRenderHint(QPainter::Antialiasing);
    view->setWindowTitle("Node Example");
    view->resize(1000, 800);
    view->show();



    //connect(circle1, &Node::circleMoved, edge, QOverload<>::of(&Edge::update));
    //connect(circle2, &Node::circleMoved, edge, QOverload<>::of(&Edge::update));

}

void MainWindow::AddEdge(QGraphicsScene* scene,Node* circle1, Node* circle2)
{
    Edge* edge = new Edge(circle1, circle2);
    QObject::connect(circle1, &Node::positionChanged, edge, &Edge::adjust);
    QObject::connect(circle2, &Node::positionChanged, edge, &Edge::adjust);
    scene->addItem(edge);
}

MainWindow::~MainWindow()
{
    delete ui;
}
