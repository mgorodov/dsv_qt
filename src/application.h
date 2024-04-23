#pragma once
#include <QApplication>

#include <ui/mainwindow.h>

namespace dsv {

class Application : QApplication
{
public:
    Application(int argc, char *argv[]);
    int run();
private:
    UI::MainWindow mainWindow_;
};

} // namespace dsv
