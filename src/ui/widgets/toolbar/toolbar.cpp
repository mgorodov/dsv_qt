#include "toolbar.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>

namespace dsv::UI {

Toolbar::Toolbar(QWidget* parent) : QGroupBox{parent} {
    settingsPanel_.setVisible(false);
    codeEditor_.setVisible(true);
    controlPanel_.setVisible(false);
    activityBar_.getButton(Activities::Code)->setChecked(true);

    connect(
        activityBar_.getButton(Activities::Settings), &QAbstractButton::toggled, &settingsPanel_,
        &SettingsPanel::setVisible
    );
    connect(activityBar_.getButton(Activities::Code), &QAbstractButton::toggled, &codeEditor_, &CodeEditor::setVisible);
    connect(
        activityBar_.getButton(Activities::Algo), &QAbstractButton::toggled, &controlPanel_, &ControlPanel::setVisible
    );

    createLayout();
}

CodeEditor* Toolbar::getCodeEditor() {
    return &codeEditor_;
}

ControlPanel* Toolbar::getControlPanel() {
    return &controlPanel_;
}

SettingsPanel* Toolbar::getSettingsPanel() {
    return &settingsPanel_;
}

void Toolbar::createLayout() {
    auto* hbox = new QHBoxLayout{this};
    hbox->addWidget(&activityBar_);
    hbox->addWidget(&settingsPanel_);
    hbox->addWidget(&codeEditor_);
    hbox->addWidget(&controlPanel_);
    hbox->setSpacing(0);
    hbox->setContentsMargins(0, 0, 0, 0);

    setLayout(hbox);
    setContentsMargins(0, 0, 0, 0);
    setMaximumWidth(370);  // TODO: fit content
}

}  // namespace dsv::UI
