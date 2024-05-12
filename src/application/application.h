#pragma once

#include <application/application_kernel.h>
#include <ui/mainwindow.h>

namespace dsv {

class Application : ApplicationKernel {
public:
    Application();
    void run();

private:
    UI::MainWindow mainWindow_;
};

}  // namespace dsv
