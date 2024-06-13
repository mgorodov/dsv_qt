#include "application.h"

namespace dsv {

Application::Application() {
    getCodeEditorModel()->subscribeToTextData(getMainCodeEditor()->textDataInPort());
    getGraphEditorModel()->subscribeToDrawData(getMainGraphEditor()->drawDataInPort());

    getMainCodeEditor()->subscribeToContentData(getCodeEditorController()->contentDataInPort());

    getMainGraphEditor()->subscribeToMouseData(getGraphEditorViewController()->mouseDataInPort());
    getMainGraphEditor()->subscribeToKeyData(getGraphEditorViewController()->keyDataInPort());
}

void Application::showMainWindow() {
    getMainWindow()->show();
}

}  // namespace dsv
