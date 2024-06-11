#pragma once

#include <QGroupBox>

namespace dsv::UI {

class SettingsPanel : public QGroupBox {
    Q_OBJECT
public:
    SettingsPanel(QWidget* parent = nullptr);
};

}  // namespace dsv::UI
