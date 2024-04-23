#include "grapheditor.h"
#include <ui/graph/edge.h>
#include <ui/graph/node.h>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace dsv::UI {

GraphEditor::GraphEditor(QWidget *parent)
    : QWidget{parent}
{
}

} // namespace dsv::UI
