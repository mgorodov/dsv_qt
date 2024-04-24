#ifndef GRAPHEDITOR_H
#define GRAPHEDITOR_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "node.h"
#include "edge.h"

namespace dsv::UI {

class GraphEditor : public QWidget
{
    Q_OBJECT
public:
    explicit GraphEditor(QWidget *parent = nullptr);
    QGraphicsScene *scene;
    QGraphicsView *view;
    void AddNode(size_t num);
    void AddEdge(size_t from, size_t to);
    void RemoveNode(size_t num);
    void RemoveEdge(size_t from, size_t to);

private:
    void PlaceNodeOnEmptySpace(Node* cur);

    std::unordered_map<size_t, Node*> nodes_;
    std::unordered_map<size_t, std::unordered_map<size_t, Edge*>> edges_;
};

} // namespace dsv::UI

#endif // GRAPHEDITOR_H
