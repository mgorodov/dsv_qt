#include "application.h"

namespace dsv {

Application::Application(int argc, char *argv[])
    : QApplication(argc, argv)
{}

int Application::run()
{
    mainWindow_.show();
    return exec();
}

} // namespace dsv
