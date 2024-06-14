#pragma once

#include <application/application_gui.h>
#include <application/application_kernel.h>

namespace dsv {

class Application : Kernel::ApplicationKernel, UI::ApplicationGUI {
public:
    Application();
    void showMainWindow();
};

}  // namespace dsv
