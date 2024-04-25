#pragma once

#include <QWidget>

namespace dsv::UI {

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void createInterface();
};

}  // namespace dsv::UI
