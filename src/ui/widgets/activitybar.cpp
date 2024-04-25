#include "activitybar.h"

#include <static/static.h>

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
    button2->setIcon(QIcon(":/icons/code-slash.svg"));
    button2->setIconSize(QSize(48, 48));
    button2->setFixedSize(70, 70);

    auto* button3 = new QPushButton(this);
    button3->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    button3->setIcon(QIcon(":/icons/code.svg"));
    button3->setIconSize(QSize(48, 48));
    button3->setFixedSize(70, 70);

    auto* vbox = new QVBoxLayout;
    vbox->addWidget(button1);
    vbox->addWidget(button2);
    vbox->addWidget(button3);
    vbox->addStretch(1);
    // vbox->setMargin(0);
    vbox->setContentsMargins(0, 0, 0, 0);
    setLayout(vbox);

    /*auto* label = new QLabel(this);
    auto hui = Static::loadPixmap(":/icons/code-slash.svg", {30, 30}, Qt::white);*/
}

void createButtons() {}

}  // namespace dsv::UI
