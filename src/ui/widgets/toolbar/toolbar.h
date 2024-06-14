#pragma once
#include <ui/views/code_editor/code_editor.h>
#include <ui/views/settings_panel/settings_panel.h>
#include <ui/widgets/control_panel.h>
#include <ui/widgets/toolbar/activity_bar.h>

namespace dsv::UI {

class Toolbar : public QGroupBox {
    Q_OBJECT
public:
    Toolbar(QWidget* parent = nullptr);
    CodeEditor* getCodeEditor();
    ControlPanel* getControlPanel();

private:
    void createLayout();

    ActivityBar activityBar_;
    SettingsPanel settingsPanel_;
    CodeEditor codeEditor_;
    ControlPanel controlPanel_;
};

}  // namespace dsv::UI
