#pragma once

#include <misc/settings.h>

#include <QGroupBox>

namespace dsv::UI {

class SettingsPanel : public QGroupBox {
    Q_OBJECT
public:
    SettingsPanel(QWidget* parent = nullptr);

private:
    Settings settings_;
};

}  // namespace dsv::UI
