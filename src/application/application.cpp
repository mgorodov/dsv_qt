#include "application.h"

#include <ui/static/static.h>

#include <QFile>

namespace dsv {

Application::Application() {
    mainWindow_.setStyleSheet(Static::loadResource(":/styles.qss"));
    graphEditorModel_.subscribeToDrawData(mainWindow_.getGraphEditor()->drawDataPort());
    mainWindow_.getGraphEditor()->subscribeToMouseData(graphEditorModel_.mouseDataInPort());
}

void Application::run() {
    mainWindow_.show();
}

}  // namespace dsv
