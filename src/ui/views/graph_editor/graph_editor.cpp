#include "graph_editor.h"

#include <ui/views/graph_editor/edge_item.h>
#include <ui/views/graph_editor/node_item.h>

namespace dsv::UI {

using DrawData = std::optional<Kernel::DrawableGraph>;
using ObserverDrawData = NSLibrary::CObserver<DrawData>;

GraphEditor::GraphEditor(QWidget *parent) : QGraphicsView(parent), scene_{new QGraphicsScene(parent)} {
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
    setScene(scene_);
    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void GraphEditor::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    const auto viewSize = size();
    scene_->setSceneRect(0, 0, viewSize.width(), viewSize.height());
    fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
}

ObserverDrawData *GraphEditor::drawDataInPort() {
    return &drawDataInPort_;
}

void GraphEditor::subscribeToMouseData(ObserverMouse *observer) {
    assert(observer);
    mouseDataOutPort_.subscribe(observer);
}

void GraphEditor::subscribeToKeyData(ObserverKey *observer) {
    assert(observer);
    keyDataOutPort_.subscribe(observer);
}

void GraphEditor::mouseDoubleClickEvent(QMouseEvent *event) {
    mouseDataOutPort_.set(MouseAction{EMouseStatus::DoubleClicked, event->button(), event->pos()});
}

void GraphEditor::mouseMoveEvent(QMouseEvent *event) {
    mouseDataOutPort_.set(MouseAction{EMouseStatus::Moved, event->button(), event->pos()});
}

void GraphEditor::mousePressEvent(QMouseEvent *event) {
    mouseDataOutPort_.set(MouseAction{EMouseStatus::Pressed, event->button(), event->pos()});
}

void GraphEditor::mouseReleaseEvent(QMouseEvent *event) {
    mouseDataOutPort_.set(MouseAction{EMouseStatus::Released, event->button(), event->pos()});
}

void GraphEditor::keyPressEvent(QKeyEvent *event) {
    keyDataOutPort_.set(KeyAction{EKeyStatus::Pressed, static_cast<Qt::Key>(event->key())});
    // event->accept();
}

void GraphEditor::keyReleaseEvent(QKeyEvent *event) {
    keyDataOutPort_.set(KeyAction{EKeyStatus::Released, static_cast<Qt::Key>(event->key())});
    // event->accept();
}

void GraphEditor::onDrawData(DrawData &&drawData) {
    if (!drawData) {
        qDebug() << "No drawData yet";
        return;
    }
    scene_->clear();

    // qDebug() << "Number of nodes: " << drawData->nodes.size();
    for (const auto &[from, toEdge] : drawData->edges) {
        for (const auto &[to, edge] : toEdge) {
            auto *edgeItem = new EdgeItem{edge};
            scene_->addItem(edgeItem);
        }
    }

    for (const auto &[index, node] : drawData->nodes) {
        auto *nodeItem = new NodeItem{index, node};
        scene_->addItem(nodeItem);
    }
}

}  // namespace dsv::UI
