#include "grapheditor.h"

#include <QGraphicsEllipseItem>

namespace dsv::UI {

GraphEditor::GraphEditor(QWidget *parent) : QGraphicsView(parent) {
    scene_ = new QGraphicsScene(parent);
    scene_->setSceneRect(0, 0, 1200, 800);
    fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
    setScene(scene_);
}

void GraphEditor::mouseDoubleClickEvent(QMouseEvent *event) {
    mouseDataOutPort_.set(MouseAction{EMouseStatus::DoubleClicked, event->pos()});
}

void GraphEditor::mouseMoveEvent(QMouseEvent *event) {
    mouseDataOutPort_.set(MouseAction{EMouseStatus::Moved, event->pos()});
}

void GraphEditor::mousePressEvent(QMouseEvent *event) {
    mouseDataOutPort_.set(MouseAction{EMouseStatus::Pressed, event->pos()});
}

void GraphEditor::mouseReleaseEvent(QMouseEvent *event) {
    mouseDataOutPort_.set(MouseAction{EMouseStatus::Released, event->pos()});
}

void GraphEditor::onDrawData(DrawData &&drawData) {
    if (!drawData) {
        qDebug() << "No drawData yet";
        return;
    }
    qDebug() << "Number of nodes: " << drawData->nodes.size();
    for (const auto &[index, node] : drawData->nodes) {
        qDebug() << index << ": " << node.position << " " << node.fill;
        auto circle = new QGraphicsEllipseItem(node.position.x(), node.position.y(), 30, 30);
        circle->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
        circle->setBrush(node.fill);
        scene_->addItem(circle);
    }
}

}  // namespace dsv::UI
