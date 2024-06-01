#include "settings_pannel.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace dsv::UI {

SettingsPannel::SettingsPannel(QWidget* parent) : QGroupBox{parent} {
    auto* grid = new QGridLayout(this);

    auto* label = new QLabel(this);
    label->setText("Settings");
    label->setAlignment(Qt::AlignCenter);

    auto* buttonTmp = new QPushButton(this);
    buttonTmp->setFixedSize(40, 40);

    auto* checkboxTmp = new QCheckBox(this);
    checkboxTmp->setFixedSize(40, 40);

    auto* textboxTmp = new QLineEdit(this);

    grid->addWidget(label, 0, 0, 1, 2);
    grid->addWidget(buttonTmp, 1, 0);
    grid->addWidget(checkboxTmp, 1, 1);
    grid->addWidget(textboxTmp, 2, 0, 1, 2);
    grid->setAlignment(Qt::AlignCenter);
    setLayout(grid);
}

}  // namespace dsv::UI
