#include "settings_panel.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace dsv::UI {

SettingsPanel::SettingsPanel(QWidget* parent) : QGroupBox{parent} {
    auto* grid = new QGridLayout(this);

    auto* label = new QLabel(this);
    label->setText("Settings");
    QFont font;
    font.setPixelSize(30);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    auto* buttonTmp = new QPushButton(this);
    buttonTmp->setFixedSize(40, 40);

    auto* weightedLabel = new QLabel();
    auto* weightedCheckBox = new QCheckBox(this);
    weightedCheckBox->setFixedSize(40, 40);

    auto* directedCheckBox = new QCheckBox(this);
    directedCheckBox->setFixedSize(40, 40);

    auto* textboxTmp = new QLineEdit(this);

    grid->addWidget(label, 0, 0, 1, 2, Qt::AlignTop);
    grid->addWidget(buttonTmp, 1, 0);
    grid->addWidget(weightedCheckBox, 1, 1);
    grid->addWidget(textboxTmp, 2, 0, 1, 2);
    setLayout(grid);
    setFixedWidth(300);
    setContentsMargins(0, 0, 0, 0);
}

}  // namespace dsv::UI
