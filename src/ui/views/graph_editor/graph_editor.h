#pragma once

#include <kernel/graph_editor/graph_editor_model.h>
#include <misc/Observer.h>
#include <misc/keyboard_action.h>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>

namespace dsv::UI {

class GraphEditor : public QGraphicsView {
    Q_OBJECT
    using DrawData = std::optional<Kernel::DrawableGraph>;
    using ObserverDrawData = NSLibrary::CObserver<DrawData>;

    using MouseData = std::optional<MouseAction>;
    using ObservableMouse = NSLibrary::CObservableDataMono<MouseData>;
    using ObserverMouse = NSLibrary::CObserver<MouseData>;

    using KeyData = std::optional<KeyAction>;
    using ObservableKey = NSLibrary::CObservableDataMono<KeyData>;
    using ObserverKey = NSLibrary::CObserver<KeyData>;

public:
    explicit GraphEditor(QWidget* parent = nullptr);
    ObserverDrawData* drawDataInPort() {
        return &drawDataInPort_;
    }
    void subscribeToMouseData(ObserverMouse* observer) {
        assert(observer);
        mouseDataOutPort_.subscribe(observer);
    }
    void subscribeToKeyData(ObserverKey* observer) {
        assert(observer);
        keyDataOutPort_.subscribe(observer);
    }

private:
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void onDrawData(DrawData&& drawData);
    ObserverDrawData drawDataInPort_ = [this](DrawData&& drawData) { onDrawData(std::move(drawData)); };
    ObservableMouse mouseDataOutPort_;
    ObservableKey keyDataOutPort_;

    QGraphicsScene* scene_;
};

}  // namespace dsv::UI
