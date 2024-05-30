#include "application.h"

namespace dsv {

Application::Application() {
    getGraphEditorModel()->subscribeToDrawData(getMainWindow()->getGraphEditor()->drawDataInPort());
    getCodeEditorModel()->subscribeToTextData(getMainWindow()->getCodeEditor()->textDataInPort());

    getMainWindow()->getGraphEditor()->subscribeToMouseData(getGraphEditorViewController()->mouseDataInPort());
    getMainWindow()->getGraphEditor()->subscribeToKeyData(getGraphEditorViewController()->keyDataInPort());
}

void Application::showMainWindow() {
    getMainWindow()->show();
}

}  // namespace dsv
