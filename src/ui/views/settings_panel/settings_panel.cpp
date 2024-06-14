#include "settings_panel.h"

namespace dsv::UI {

SettingsPanel::SettingsPanel(QWidget* parent)
    : QGroupBox{parent}, radiusSelector{Qt::Horizontal}, fpsSelector{Qt::Horizontal} {
    createLayout();
}

void SettingsPanel::subscribeToSettingsData(ObserverSettingsData* observer) {
    assert(observer);
    settingsDataOutPort_.subscribe(observer);
}

void SettingsPanel::weightedChanged(Qt::CheckState state) {
    settings_.weighted = state;
    settingsDataOutPort_.set(settings_);
}
void SettingsPanel::directedChanged(Qt::CheckState state) {
    settings_.directed = state;
    settingsDataOutPort_.set(settings_);
}
void SettingsPanel::radiusChanged(int value) {
    settings_.nodeRadius = value;
    settingsDataOutPort_.set(settings_);
}

void SettingsPanel::fpsChanged(int value) {
    settings_.animationFPS = 1000.0 / value;
    settingsDataOutPort_.set(settings_);
}

void SettingsPanel::createLayout() {
    auto* grid = new QGridLayout(this);

    label.setText("Settings");
    QFont font;
    font.setPixelSize(30);
    label.setFont(font);
    label.setAlignment(Qt::AlignCenter);

    weightedLabel.setText("Is weighted");
    font.setPixelSize(18);
    weightedLabel.setFont(font);
    weightedLabel.setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

    weightedCheckBox.setFixedSize(30, 30);
    connect(&weightedCheckBox, &QCheckBox::checkStateChanged, this, &SettingsPanel::weightedChanged);

    directedLabel.setText("Is directed");
    font.setPixelSize(18);
    directedLabel.setFont(font);
    directedLabel.setAlignment(Qt::AlignCenter);

    directedCheckBox.setFixedSize(30, 30);
    connect(&directedCheckBox, &QCheckBox::checkStateChanged, this, &SettingsPanel::directedChanged);

    radiusLabel.setText("Node radius");
    font.setPixelSize(18);
    radiusLabel.setFont(font);
    radiusLabel.setAlignment(Qt::AlignCenter);

    radiusSelector.setMinimum(20);
    radiusSelector.setMaximum(40);
    radiusSelector.setValue(30);
    radiusSelector.setFixedWidth(150);
    connect(&radiusSelector, &QSlider::valueChanged, this, &SettingsPanel::radiusChanged);

    fpsLabel.setText("Animation FPS");
    font.setPixelSize(18);
    fpsLabel.setFont(font);
    fpsLabel.setAlignment(Qt::AlignCenter);

    fpsSelector.setMinimum(100);
    fpsSelector.setMaximum(1000);
    fpsSelector.setValue(500);
    fpsSelector.setFixedWidth(150);
    connect(&fpsSelector, &QSlider::valueChanged, this, &SettingsPanel::fpsChanged);

    grid->addWidget(&label, 0, 0, 1, 6, Qt::AlignTop);
    grid->addWidget(&weightedLabel, 1, 0, 1, 4, Qt::AlignCenter);
    grid->addWidget(&weightedCheckBox, 1, 4, 1, 2, Qt::AlignCenter);

    grid->addWidget(&directedLabel, 2, 0, 1, 4, Qt::AlignCenter);
    grid->addWidget(&directedCheckBox, 2, 4, 1, 2, Qt::AlignCenter);

    grid->addWidget(&radiusLabel, 3, 0, 1, 2, Qt::AlignCenter);
    grid->addWidget(&radiusSelector, 3, 2, 1, 4, Qt::AlignCenter);

    grid->addWidget(&fpsLabel, 4, 0, 1, 2, Qt::AlignCenter);
    grid->addWidget(&fpsSelector, 4, 2, 1, 4, Qt::AlignCenter);

    auto* empty = new QLabel;
    grid->addWidget(empty, 5, 0, 9, 6, Qt::AlignTop);

    setLayout(grid);
    setFixedWidth(300);
    setContentsMargins(0, 0, 0, 0);
}

}  // namespace dsv::UI
