#pragma once

#include <ui/mainwindow.h>

namespace dsv {

class Application {
public:
    Application();
    void run();

private:
    UI::MainWindow mainWindow_;
};
}  // namespace dsv
