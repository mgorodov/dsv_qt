#include "toolbar.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>

namespace dsv::UI {

Toolbar::Toolbar(QWidget* parent) : QGroupBox{parent}, activityBar_{new QGroupBox(this)} {
    constructActivityBar();
    createLayout();
    settingsPannel_.setVisible(false);
    codeEditor_.setVisible(true);
}

CodeEditor* Toolbar::getCodeEditor() {
    return &codeEditor_;
}

void Toolbar::constructActivityBar() {
    auto* settingsButton = new QPushButton(this);
    settingsButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    settingsButton->setIcon(QIcon(":/icons/settings.svg"));
    settingsButton->setIconSize(QSize(48, 48));
    settingsButton->setFixedSize(70, 70);
    settingsButton->setCheckable(true);
    connect(settingsButton, &QPushButton::toggled, &settingsPannel_, &SettingsPannel::setVisible);

    auto* codeButton = new QPushButton(this);
    codeButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    codeButton->setIcon(QIcon(":/icons/code.svg"));
    codeButton->setIconSize(QSize(48, 48));
    codeButton->setFixedSize(70, 70);
    codeButton->setCheckable(true);
    codeButton->setChecked(true);
    connect(codeButton, &QPushButton::toggled, &codeEditor_, &CodeEditor::setVisible);

    auto* buttons = new QButtonGroup{this};
    buttons->addButton(settingsButton);
    buttons->addButton(codeButton);

    auto* vbox = new QVBoxLayout(this);
    for (auto* button : buttons->buttons()) vbox->addWidget(button);
    vbox->addStretch(1);
    vbox->setSpacing(0);
    vbox->setContentsMargins(0, 0, 0, 0);

    activityBar_->setLayout(vbox);
    activityBar_->setFixedWidth(70);
}

void Toolbar::createLayout() {
    auto* hbox = new QHBoxLayout(this);
    hbox->addWidget(activityBar_);
    hbox->addWidget(&settingsPannel_);
    hbox->addWidget(&codeEditor_);
    // hbox->addStretch(1);
    hbox->setContentsMargins(0, 0, 0, 0);
    hbox->setSpacing(0);

    setLayout(hbox);
    setContentsMargins(0, 0, 0, 0);
    setMaximumWidth(370);
}

}  // namespace dsv::UI
