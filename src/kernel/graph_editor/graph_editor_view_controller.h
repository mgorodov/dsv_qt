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
    GraphEditorViewController(GraphEditorModel& graphEditorModel);
    ObserverMouseData* mouseDataInPort() {
        return &mouseDataInPort_;
    }
    ObserverKeyData* keyDataInPort() {
        return &keyDataInPort_;
    }

private:
    GraphEditorModel& graphEditorModel_;
    void handleDoubleClick();
    void onMouseData(MouseData&& mouseData);
    void onKeyData(KeyData&& keyData);

    ObserverMouseData mouseDataInPort_ = [this](MouseData&& mouseData) { onMouseData(std::move(mouseData)); };
    ObserverKeyData keyDataInPort_ = [this](KeyData&& keyData) { onKeyData(std::move(keyData)); };
};

}  // namespace dsv::Kernel
