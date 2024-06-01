#pragma once

#include <QGroupBox>

namespace dsv::UI {

class SettingsPannel : public QGroupBox {
    Q_OBJECT
public:
    SettingsPannel(QWidget* parent = nullptr);
};

}  // namespace dsv::UI
