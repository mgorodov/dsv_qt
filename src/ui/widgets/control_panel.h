#pragma once

#include <QGroupBox>

namespace dsv::UI {

class ControlPanel : public QGroupBox {
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = nullptr);
    void createLayout();
};

}  // namespace dsv::UI
