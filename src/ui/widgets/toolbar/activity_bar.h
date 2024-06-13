#pragma once

#include <QButtonGroup>
#include <QGroupBox>

namespace dsv::UI {

enum class Activities { Settings, Code, Algo };

class ActivityBar : public QGroupBox {
    Q_OBJECT
public:
    ActivityBar(QWidget* parent = nullptr);
    QAbstractButton* getButton(Activities id);

private:
    void createSettingsButton();
    void createCodeButton();
    void createAlgoButton();
    QButtonGroup buttons_;
};

}  // namespace dsv::UI
