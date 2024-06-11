#pragma once

#include <kernel/data_model/data_model.h>
#include <misc/edit_action.h>

namespace dsv::Kernel {

class GraphEditorModelController {
    using EditData = std::optional<EditAction>;
    using ObserverEditData = NSLibrary::CObserver<EditData>;

public:
    void connect(DataModel* dataModel);
    ObserverEditData* editDataInPort();

private:
    void handleAddingNode(const size_t index);
    void handleRemovingNode(const size_t index);
    void onEditData(EditData&& mouseData);

    ObserverEditData editDataInPort_ = [this](EditData&& editData) { onEditData(std::move(editData)); };

    DataModel* dataModel_ = nullptr;
};

}  // namespace dsv::Kernel
