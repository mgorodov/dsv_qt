#include "application.h"

namespace dsv {

Application::Application() {
    getCodeEditorModel()->subscribeToTextData(getMainWindow()->getCodeEditor()->textDataInPort());
    getGraphEditorModel()->subscribeToDrawData(getMainWindow()->getGraphEditor()->drawDataInPort());

    getMainWindow()->getCodeEditor()->subscribeToContentData(getCodeEditorController()->contentDataInPort());

    getMainWindow()->getGraphEditor()->subscribeToMouseData(getGraphEditorViewController()->mouseDataInPort());
    getMainWindow()->getGraphEditor()->subscribeToKeyData(getGraphEditorViewController()->keyDataInPort());
}

void Application::showMainWindow() {
    getMainWindow()->show();
}

}  // namespace dsv
