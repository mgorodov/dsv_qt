#include "application.h"

#include <static/static.h>

#include <QFile>

namespace dsv {

Application::Application() {
    mainWindow_.setStyleSheet(Static::loadResource(":/styles.qss"));
}

void Application::run() {
    mainWindow_.show();
}

}  // namespace dsv
