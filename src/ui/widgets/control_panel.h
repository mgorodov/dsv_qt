#pragma once

#include <QWidget>

namespace dsv::UI {

class ControlPanel : public QWidget {
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = nullptr);

signals:
};

}  // namespace dsv::UI
