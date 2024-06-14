#pragma once

#include <kernel/settings_pannel/settings.h>
#include <misc/Observer.h>

namespace dsv::UI {

class SettingsModel {
    using SettingsData = std::optional<Settings>;
    using ObservableSettingsData = NSLibrary::CObservable<SettingsData>;
    using ObserverSettingsData = NSLibrary::CObserver<SettingsData>;

public:
    SettingsModel();
    void subscribe(ObserverSettingsData* observer);

    void setNodeSize(qreal nodeSize);

private:
    SettingsData settings_;
    ObservableSettingsData port_ = [this]() -> const SettingsData& { return settings_; };
};

}  // namespace dsv::UI
