#include "control_panel.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace dsv::UI {

ControlPanel::ControlPanel(QWidget* parent) : QGroupBox{parent} {
    createLayout();
}

void ControlPanel::createLayout() {
    auto* grid = new QGridLayout(this);

    auto* label = new QLabel(this);
    label->setText("Control panel");
    QFont font;
    font.setPixelSize(30);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    // label->setStyleSheet("border: 2px solid yellow");

    auto* label1 = new QLabel(this);
    label1->setText("Algorithm:");
    font.setPixelSize(14);
    label1->setFont(font);
    label1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label1->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    // label1->setStyleSheet("border: none");
    // label1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto* selector = new QComboBox(this);
    // selector->setStyleSheet("border: none");
    selector->addItem("DFS");
    selector->addItem("BFS");
    selector->addItem("Dijkstra");
    selector->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto* runButton = new QPushButton(this);
    runButton->setFixedHeight(40);
    runButton->setText("Run");
    runButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto* stepBackwardButton = new QPushButton(this);
    stepBackwardButton->setFixedHeight(40);
    stepBackwardButton->setText("Step backward");

    auto* stepForwardButton = new QPushButton(this);
    stepForwardButton->setFixedHeight(40);
    stepForwardButton->setText("Step forward");

    auto* stopButton = new QPushButton(this);
    stopButton->setFixedHeight(40);
    stopButton->setText("Stop");

    grid->addWidget(label, 0, 0, 1, 6, Qt::AlignTop);
    grid->addWidget(label1, 1, 0, 1, 2, Qt::AlignTop);
    grid->addWidget(selector, 1, 2, 1, 4, Qt::AlignTop);
    grid->addWidget(runButton, 2, 0, 1, 4, Qt::AlignTop);
    grid->addWidget(stopButton, 2, 4, 1, 2, Qt::AlignTop);
    grid->addWidget(stepBackwardButton, 3, 0, 10, 3, Qt::AlignTop);
    grid->addWidget(stepForwardButton, 3, 3, 10, 3, Qt::AlignTop);

    // grid->addWidget(checkboxTmp, 1, 1);
    // grid->addWidget(textboxTmp, 2, 0, 1, 2);
    grid->setSpacing(0);
    // grid->setContentsMargins(0, 0, 0, 0);
    setLayout(grid);
    setFixedWidth(300);
    setContentsMargins(0, 0, 0, 0);
}

}  // namespace dsv::UI
