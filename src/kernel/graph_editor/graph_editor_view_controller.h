#pragma once

#include <kernel/graph_editor/graph_editor_model.h>
#include <misc/algorithm_action.h>
#include <misc/keyboard_action.h>
#include <misc/mouse_action.h>
#include <misc/Observer.h>

namespace dsv::Kernel {

struct DragableNode {
    size_t index;
    double xDist;
    double yDist;
};

class GraphEditorViewController {
    using MouseData = std::optional<MouseAction>;
    using ObserverMouseData = NSLibrary::CObserver<MouseData>;

    using KeyData = std::optional<KeyAction>;
    using ObserverKeyData = NSLibrary::CObserver<KeyData>;

    using AlgoData = std::optional<AlgorithmAction>;
    using ObserverAlgoData = NSLibrary::CObserver<AlgoData>;

public:
    void connect(GraphEditorModel* graphEditorModel);

    ObserverMouseData* mouseDataInPort();
    ObserverKeyData* keyDataInPort();
    ObserverAlgoData* algoDataInPort();

private:
    void onMouseData(MouseData&& mouseData);
    void onKeyData(KeyData&& keyData);
    void onAlgoData(AlgoData&& algoData);

    void handleAddNodeInRandomPos();
    void handleAddNodeInMousePos();
    void handleChangeActive(const QPointF pos);
    void handleRemoveAllActiveNodes();
    void handleChangeLabel(const QPointF pos);
    void handleAddDragableNode(const QPointF pos);
    void handleRemoveDragableNode(const QPointF pos);
    void handleMoveDragableNode(const QPointF pos);
    void handleAddEdges();
    void handleRemoveEdges();
    void handleStartAlgorithm(size_t index, EAlgorithm algo);
    void handleEndAlgorithm();

    std::optional<size_t> getNodeInPos(const QPointF pos);

    ObserverMouseData mouseDataInPort_ = [this](MouseData&& mouseData) { onMouseData(std::move(mouseData)); };
    ObserverKeyData keyDataInPort_ = [this](KeyData&& keyData) { onKeyData(std::move(keyData)); };
    ObserverAlgoData algoDataInPort_ = [this](AlgoData&& algoData) { onAlgoData(std::move(algoData)); };

    GraphEditorModel* graphEditorModel_ = nullptr;
    std::optional<QPointF> mousePos_ = std::nullopt;
    std::optional<DragableNode> dragNode_ = std::nullopt;
};

}  // namespace dsv::Kernel
