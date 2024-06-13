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

    // auto* buttonTmp = new QPushButton(this);
    // buttonTmp->setFixedSize(40, 40);

    auto* weightedLabel = new QLabel();
    weightedLabel->setText("Is weighted");
    font.setPixelSize(18);
    weightedLabel->setFont(font);

    auto* weightedCheckBox = new QCheckBox(this);
    weightedCheckBox->setFixedSize(40, 40);

    auto* directedLabel = new QLabel();
    directedLabel->setText("Is directed");
    font.setPixelSize(18);
    directedLabel->setFont(font);

    auto* directedCheckBox = new QCheckBox(this);
    directedCheckBox->setFixedSize(40, 40);

    // auto* textboxTmp = new QLineEdit(this);

    grid->addWidget(label, 0, 0, 1, 6, Qt::AlignTop);
    grid->addWidget(weightedLabel, 1, 0, 1, 4, Qt::AlignTop);
    grid->addWidget(weightedCheckBox, 1, 4, 1, 2, Qt::AlignTop);
    grid->addWidget(directedLabel, 2, 0, 8, 4, Qt::AlignTop);
    grid->addWidget(directedCheckBox, 2, 4, 8, 2, Qt::AlignTop);
    setLayout(grid);
    setFixedWidth(300);
    setContentsMargins(0, 0, 0, 0);
}

}  // namespace dsv::UI
