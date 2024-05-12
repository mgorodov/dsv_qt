#pragma once

#include <kernel/graph_editor/graph_editor_model.h>
#include <misc/Observer.h>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

namespace dsv::UI {

class GraphEditor : public QGraphicsView {
    Q_OBJECT
    using DrawData = std::optional<Kernel::DrawableGraph>;
    using ObserverDrawData = NSLibrary::CObserver<DrawData>;

    using MouseData = std::optional<MouseAction>;
    using ObservableMouse = NSLibrary::CObservableDataMono<MouseData>;
    using ObserverMouse = NSLibrary::CObserver<MouseData>;

public:
    explicit GraphEditor(QWidget* parent = nullptr);
    ObserverDrawData* drawDataPort() {
        return &drawDataInPort_;
    }
    void subscribeToMouseData(ObserverMouse* observer) {
        assert(observer);
        mouseDataOutPort_.subscribe(observer);
    }

private:
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void onDrawData(DrawData&& drawData);
    ObserverDrawData drawDataInPort_ = [this](DrawData&& drawData) { onDrawData(std::move(drawData)); };
    ObservableMouse mouseDataOutPort_;

    QGraphicsScene* scene_;
};

}  // namespace dsv::UI
