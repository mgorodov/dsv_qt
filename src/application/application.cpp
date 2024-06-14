#include "application.h"

namespace dsv {

Application::Application() {
    getCodeEditorModel()->subscribeToTextData(getMainCodeEditor()->textDataInPort());
    getGraphEditorModel()->subscribeToDrawData(getMainGraphEditor()->drawDataInPort());
    getGraphEditorModel()->subscribeToDrawData(getMainControlPanel()->drawDataInPort());

    getMainCodeEditor()->subscribeToContentData(getCodeEditorController()->contentDataInPort());

    getMainGraphEditor()->subscribeToMouseData(getGraphEditorViewController()->mouseDataInPort());
    getMainGraphEditor()->subscribeToKeyData(getGraphEditorViewController()->keyDataInPort());
    getMainControlPanel()->subscribeToAlgoData(getGraphEditorViewController()->algoDataInPort());
}

void Application::showMainWindow() {
    getMainWindow()->show();
}

}  // namespace dsv
