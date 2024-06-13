#include "activity_bar.h"

#include <QPushButton>
#include <QVBoxLayout>

namespace dsv::UI {

ActivityBar::ActivityBar(QWidget* parent) : QGroupBox{parent} {
    createSettingsButton();
    createCodeButton();
    createAlgoButton();

    auto* vbox = new QVBoxLayout{this};
    for (auto* button : buttons_.buttons()) {
        vbox->addWidget(button);
    }
    vbox->addStretch(1);
    vbox->setSpacing(0);
    vbox->setContentsMargins(0, 0, 0, 0);

    setLayout(vbox);
    setFixedWidth(70);  // TODO: fit content
}

QAbstractButton* ActivityBar::getButton(Activities id) {
    return buttons_.button(static_cast<int>(id));
}

void ActivityBar::createSettingsButton() {
    auto* settingsButton = new QPushButton(this);
    settingsButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    settingsButton->setIcon(QIcon(":/icons/settings.svg"));
    settingsButton->setIconSize(QSize(48, 48));
    settingsButton->setFixedSize(70, 70);
    settingsButton->setCheckable(true);

    buttons_.addButton(settingsButton, static_cast<int>(Activities::Settings));
}

void ActivityBar::createCodeButton() {
    auto* codeButton = new QPushButton(this);
    codeButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    codeButton->setIcon(QIcon(":/icons/code.svg"));
    codeButton->setIconSize(QSize(48, 48));
    codeButton->setFixedSize(70, 70);
    codeButton->setCheckable(true);

    buttons_.addButton(codeButton, static_cast<int>(Activities::Code));
}

void ActivityBar::createAlgoButton() {
    auto* algoButton = new QPushButton(this);
    algoButton->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    algoButton->setIcon(QIcon(":/icons/algo.svg"));
    algoButton->setIconSize(QSize(48, 48));
    algoButton->setFixedSize(70, 70);
    algoButton->setCheckable(true);

    buttons_.addButton(algoButton, static_cast<int>(Activities::Algo));
}

}  // namespace dsv::UI
