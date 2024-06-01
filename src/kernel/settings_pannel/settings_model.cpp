#include "settings_model.h"

namespace dsv::UI {

SettingsModel::SettingsModel() : settings_{std::in_place_t{}} {}

void SettingsModel::subscribe(ObserverSettingsData* observer) {
    assert(observer);
    port_.subscribe(observer);
}

void SettingsModel::setNodeSize(qreal nodeSize) {
    assert(settings_.has_value());
    settings_->nodeSize = nodeSize;
    port_.notify();
}

}  // namespace dsv::UI
