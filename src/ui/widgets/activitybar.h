#pragma once

#include <QGroupBox>

namespace dsv::UI {

class ActivityBar : public QGroupBox {
    Q_OBJECT
public:
    ActivityBar(QWidget* parent = nullptr);
};

}  // namespace dsv::UI
