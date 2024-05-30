#pragma once

#include <ui/mainwindow.h>

#include "application_kernel.h"

namespace dsv {

class Application : ApplicationKernel {
public:
    Application();
    void show();

private:
    UI::MainWindow mainWindow_;
};

}  // namespace dsv
