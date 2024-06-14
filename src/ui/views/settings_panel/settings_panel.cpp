#include "settings_panel.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>

namespace dsv::UI {

SettingsPanel::SettingsPanel(QWidget* parent) : QGroupBox{parent} {
    auto* grid = new QGridLayout(this);

    auto* label = new QLabel;
    label->setText("Settings");
    QFont font;
    font.setPixelSize(30);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    // auto* buttonTmp = new QPushButton(this);
    // buttonTmp->setFixedSize(40, 40);

    auto* weightedLabel = new QLabel;
    weightedLabel->setText("Is weighted");
    font.setPixelSize(18);
    weightedLabel->setFont(font);
    weightedLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

    auto* weightedCheckBox = new QCheckBox;
    weightedCheckBox->setFixedSize(30, 30);

    auto* directedLabel = new QLabel;
    directedLabel->setText("Is directed");
    font.setPixelSize(18);
    directedLabel->setFont(font);
    directedLabel->setAlignment(Qt::AlignCenter);

    auto* directedCheckBox = new QCheckBox;
    directedCheckBox->setFixedSize(30, 30);

    auto* radiusLabel = new QLabel;
    radiusLabel->setText("Node radius");
    font.setPixelSize(18);
    radiusLabel->setFont(font);
    radiusLabel->setAlignment(Qt::AlignCenter);

    auto* radiusSelector = new QSlider(Qt::Horizontal);
    radiusSelector->setMinimum(20);
    radiusSelector->setMaximum(40);
    radiusSelector->setValue(30);
    radiusSelector->setFixedWidth(150);
    // radiusSelector->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // auto* textboxTmp = new QLineEdit(this);

    grid->addWidget(label, 0, 0, 1, 6, Qt::AlignTop);
    grid->addWidget(weightedLabel, 1, 0, 1, 4, Qt::AlignCenter);
    grid->addWidget(weightedCheckBox, 1, 4, 1, 2, Qt::AlignCenter);

    grid->addWidget(directedLabel, 2, 0, 1, 4, Qt::AlignCenter);
    grid->addWidget(directedCheckBox, 2, 4, 1, 2, Qt::AlignCenter);

    grid->addWidget(radiusLabel, 3, 0, 1, 2, Qt::AlignCenter);
    grid->addWidget(radiusSelector, 3, 2, 1, 4, Qt::AlignCenter);

    auto* empty = new QLabel;
    grid->addWidget(empty, 4, 0, 9, 6, Qt::AlignTop);

    setLayout(grid);
    setFixedWidth(300);
    setContentsMargins(0, 0, 0, 0);
}

}  // namespace dsv::UI
