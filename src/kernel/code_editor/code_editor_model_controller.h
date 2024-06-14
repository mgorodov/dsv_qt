#pragma once

#include <kernel/data_model/data_model.h>
#include <misc/edit_action.h>

namespace dsv::Kernel {

class CodeEditorModelController {
    using GraphData = std::optional<Graph>;
    using ObserverGraphData = NSLibrary::CObserver<GraphData>;

public:
    void connect(DataModel* dataModel);
    ObserverGraphData* graphDataInPort();

private:
    void onGraphData(GraphData&& graphData);

    ObserverGraphData graphDataInPort_ = [this](GraphData&& graphData) { onGraphData(std::move(graphData)); };

    DataModel* dataModel_ = nullptr;
};

}  // namespace dsv::Kernel
