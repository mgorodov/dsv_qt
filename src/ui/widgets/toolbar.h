#pragma once
#include <ui/views/code_editor/code_editor.h>
#include <ui/widgets/settings_pannel.h>

#include <QGroupBox>

namespace dsv::UI {

class Toolbar : public QGroupBox {
    Q_OBJECT
public:
    Toolbar(QWidget* parent = nullptr);
    CodeEditor* getCodeEditor();

private:
    void constructActivityBar();
    void createLayout();

    QGroupBox* activityBar_;
    SettingsPannel settingsPannel_;
    CodeEditor codeEditor_;
};

}  // namespace dsv::UI
