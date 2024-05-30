#include "activitybar.h"

#include <ui/static/static.h>

#include <QPushButton>
#include <QVBoxLayout>

namespace dsv::UI {

ActivityBar::ActivityBar(QWidget* parent) : QGroupBox(parent) {
    auto* button1 = new QPushButton(this);
    button1->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    button1->setIcon(QIcon(":/icons/settings.svg"));
    button1->setIconSize(QSize(48, 48));
    button1->setFixedSize(70, 70);

    auto* button2 = new QPushButton(this);
    button2->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    button2->setIcon(QIcon(":/icons/code.svg"));
    button2->setIconSize(QSize(48, 48));
    button2->setFixedSize(70, 70);

    auto* vbox = new QVBoxLayout(this);
    vbox->addWidget(button1);
    vbox->addWidget(button2);
    vbox->addStretch(1);
    // vbox->setMargin(0);
    vbox->setContentsMargins(0, 0, 0, 0);
    setLayout(vbox);

    /*auto* label = new QLabel(this);
    auto hui = Static::loadPixmap(":/icons/code-slash.svg", {30, 30}, Qt::white);*/
}

void createButtons() {}

}  // namespace dsv::UI
