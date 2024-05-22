#include "application.h"

#include <ui/static/static.h>

#include <QFile>

namespace dsv {

Application::Application() {
    mainWindow_.setStyleSheet(Static::loadResource(":/styles.qss"));
    graphEditorModel_.subscribeToDrawData(mainWindow_.getGraphEditor()->drawDataInPort());
    codeEditorModel_.subscribeToTextData(mainWindow_.getCodeEditor()->textDataInPort());
    mainWindow_.getGraphEditor()->subscribeToMouseData(graphEditorViewController_.mouseDataInPort());
}

void Application::run() {
    mainWindow_.show();
}

}  // namespace dsv
