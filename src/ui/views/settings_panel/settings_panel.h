#pragma once

#include <misc/Observer.h>
#include <misc/settings.h>

#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>

namespace dsv::UI {

class SettingsPanel : public QGroupBox {
    Q_OBJECT
    using SettingsData = std::optional<Settings>;
    using ObservableSettingsData = NSLibrary::CObservableDataMono<SettingsData>;
    using ObserverSettingsData = NSLibrary::CObserver<SettingsData>;

public:
    SettingsPanel(QWidget* parent = nullptr);
    void subscribeToSettingsData(ObserverSettingsData* observer);

private slots:
    void weightedChanged(Qt::CheckState state);
    void directedChanged(Qt::CheckState state);
    void radiusChanged(int value);
    void fpsChanged(int value);

private:
    void createLayout();
    Settings settings_;

    QLabel label;
    QLabel weightedLabel;
    QCheckBox weightedCheckBox;
    QLabel directedLabel;
    QCheckBox directedCheckBox;
    QLabel radiusLabel;
    QSlider radiusSelector;
    QLabel fpsLabel;
    QSlider fpsSelector;

    ObservableSettingsData settingsDataOutPort_;
};

}  // namespace dsv::UI
