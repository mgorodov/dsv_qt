#pragma once
#include <ui/views/code_editor/code_editor.h>
#include <ui/views/settings_pannel/settings_pannel.h>
#include <ui/widgets/activity_bar.h>

namespace dsv::UI {

class Toolbar : public QGroupBox {
    Q_OBJECT
public:
    Toolbar(QWidget* parent = nullptr);
    CodeEditor* getCodeEditor();

private:
    void createLayout();

    ActivityBar activityBar_;
    SettingsPannel settingsPannel_;
    CodeEditor codeEditor_;
};

}  // namespace dsv::UI
