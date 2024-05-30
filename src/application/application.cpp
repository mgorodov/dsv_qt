#include "application.h"

#include <ui/static/static.h>

#include <QFile>

namespace dsv {

Application::Application() : mainWindow_{*GetCodeEditorController()} {
    mainWindow_.setStyleSheet(Static::loadResource(":/styles.qss"));
    GetGraphEditorModel()->subscribeToDrawData(mainWindow_.getGraphEditor()->drawDataInPort());
    GetCodeEditorModel()->subscribeToTextData(mainWindow_.getCodeEditor()->textDataInPort());
    mainWindow_.getGraphEditor()->subscribeToMouseData(GetGraphEditorViewController()->mouseDataInPort());
    mainWindow_.getGraphEditor()->subscribeToKeyData(GetGraphEditorViewController()->keyDataInPort());
}

void Application::show() {
    mainWindow_.show();
}

}  // namespace dsv
