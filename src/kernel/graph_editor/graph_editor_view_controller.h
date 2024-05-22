#pragma once

#include <kernel/graph_editor/graph_editor_model.h>
#include <misc/mouse_action.h>
#include <misc/Observer.h>

namespace dsv::Kernel {

class GraphEditorViewController {
    using MouseData = std::optional<MouseAction>;
    using ObserverMouseData = NSLibrary::CObserver<MouseData>;

public:
    GraphEditorViewController(GraphEditorModel& graphEditorModel);
    ObserverMouseData* mouseDataInPort() {
        return &mouseDataInPort_;
    }

private:
    GraphEditorModel& graphEditorModel_;
    void handleDoubleClick();
    void onMouseData(MouseData&& mouseData);

    ObserverMouseData mouseDataInPort_ = [this](MouseData&& mouseData) { onMouseData(std::move(mouseData)); };

};

}  // namespace dsv::Kernel
