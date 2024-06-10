#pragma once

#include <kernel/graph_editor/graph_editor_model.h>
#include <misc/keyboard_action.h>
#include <misc/mouse_action.h>
#include <misc/Observer.h>

namespace dsv::Kernel {

class GraphEditorViewController {
    using MouseData = std::optional<MouseAction>;
    using ObserverMouseData = NSLibrary::CObserver<MouseData>;

    using KeyData = std::optional<KeyAction>;
    using ObserverKeyData = NSLibrary::CObserver<KeyData>;

public:
    void connect(GraphEditorModel* graphEditorModel);

    ObserverMouseData* mouseDataInPort();
    ObserverKeyData* keyDataInPort();

private:
    void onMouseData(MouseData&& mouseData);
    void onKeyData(KeyData&& keyData);
    void handleAddNodeInRandomPos();
    void handleAddNodeInMousePos();
    void handleChangeActive(const QPointF pos);
    std::optional<size_t> getNodeInPos(const QPointF pos);

    ObserverMouseData mouseDataInPort_ = [this](MouseData&& mouseData) { onMouseData(std::move(mouseData)); };
    ObserverKeyData keyDataInPort_ = [this](KeyData&& keyData) { onKeyData(std::move(keyData)); };

    GraphEditorModel* graphEditorModel_ = nullptr;
    std::optional<QPointF> mousePos_ = std::nullopt;
};

}  // namespace dsv::Kernel
