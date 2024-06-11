#include "toolbar.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>

namespace dsv::UI {

Toolbar::Toolbar(QWidget* parent) : QGroupBox{parent} {
    settingsPanel_.setVisible(false);
    codeEditor_.setVisible(true);
    activityBar_.getButton(Activities::Code)->setChecked(true);

    connect(
        activityBar_.getButton(Activities::Settings), &QAbstractButton::toggled, &settingsPanel_,
        &SettingsPanel::setVisible
    );
    connect(activityBar_.getButton(Activities::Code), &QAbstractButton::toggled, &codeEditor_, &CodeEditor::setVisible);

    createLayout();
}

CodeEditor* Toolbar::getCodeEditor() {
    return &codeEditor_;
}

void Toolbar::createLayout() {
    auto* hbox = new QHBoxLayout{this};
    hbox->addWidget(&activityBar_);
    hbox->addWidget(&settingsPanel_);
    hbox->addWidget(&codeEditor_);
    hbox->setSpacing(0);
    hbox->setContentsMargins(0, 0, 0, 0);

    setLayout(hbox);
    setContentsMargins(0, 0, 0, 0);
    setMaximumWidth(370);  // TODO: fit content
}

}  // namespace dsv::UI
