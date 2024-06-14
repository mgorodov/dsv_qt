#include "control_panel.h"

namespace dsv::UI {

using DrawData = std::optional<Kernel::DrawableGraph>;
using ObserverDrawData = NSLibrary::CObserver<DrawData>;

using AlgoData = std::optional<AlgorithmAction>;
using ObservableAlgoData = NSLibrary::CObservableDataMono<AlgoData>;
using ObserverAlgoData = NSLibrary::CObserver<AlgoData>;

ControlPanel::ControlPanel(QWidget* parent) : QGroupBox{parent} {
    createLayout();
}

ObserverDrawData* ControlPanel::drawDataInPort() {
    return &drawDataInPort_;
}

void ControlPanel::onDrawData(DrawData&& drawData) {
    if (!drawData) {
        qDebug() << "No drawData yet in ControlPanel";
        return;
    }
    algoOutput.setPlainText(drawData->algorithmOutput);
}

void ControlPanel::subscribeToAlgoData(ObserverAlgoData* observer) {
    assert(observer);
    algoDataOutPort_.subscribe(observer);
}

void ControlPanel::runClicked() {
    algoDataOutPort_.set(AlgorithmAction{EControlButton::Run, currentAlgorithm_, startVertex_});
}

void ControlPanel::stopClicked() {
    algoDataOutPort_.set(AlgorithmAction{EControlButton::Stop, currentAlgorithm_, startVertex_});
}

void ControlPanel::backwardClicked() {
    algoDataOutPort_.set(AlgorithmAction{EControlButton::Backward, currentAlgorithm_, startVertex_});
}

void ControlPanel::forwardClicked() {
    algoDataOutPort_.set(AlgorithmAction{EControlButton::Forward, currentAlgorithm_, startVertex_});
}

void ControlPanel::algoChanged(size_t index) {
    currentAlgorithm_ = static_cast<EAlgorithm>(index);
}

void ControlPanel::startVertexChanged(const QString& text) {
    bool ok;
    int val = text.toInt(&ok);
    if (ok) {
        startVertex_ = val;
    }
}

void ControlPanel::createLayout() {
    auto* grid = new QGridLayout(this);

    label.setText("Control panel");
    QFont font;
    font.setPixelSize(30);
    label.setFont(font);
    label.setAlignment(Qt::AlignCenter);

    algoLabel.setText("Algorithm:");
    font.setPixelSize(14);
    algoLabel.setFont(font);
    algoLabel.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    algoLabel.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // selector.setStyleSheet("border: none");
    selector.addItem("DFS");
    selector.addItem("BFS");
    selector.addItem("Prim");
    selector.addItem("Kruskal");
    selector.addItem("Dijkstra");
    selector.setSizeAdjustPolicy(QComboBox::AdjustToContents);
    connect(&selector, &QComboBox::currentIndexChanged, this, &ControlPanel::algoChanged);

    runButton.setFixedHeight(40);
    runButton.setText("Run");
    runButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(&runButton, &QPushButton::clicked, this, &ControlPanel::runClicked);

    stopButton.setFixedHeight(40);
    stopButton.setText("Stop");
    connect(&stopButton, &QPushButton::clicked, this, &ControlPanel::stopClicked);

    stepBackwardButton.setFixedHeight(40);
    stepBackwardButton.setText("Step backward");
    connect(&stepBackwardButton, &QPushButton::clicked, this, &ControlPanel::backwardClicked);

    stepForwardButton.setFixedHeight(40);
    stepForwardButton.setText("Step forward");
    connect(&stepForwardButton, &QPushButton::clicked, this, &ControlPanel::forwardClicked);

    startVertexLabel.setText("Start vertex:");
    font.setPixelSize(18);
    startVertexLabel.setFont(font);
    startVertexLabel.setAlignment(Qt::AlignCenter);

    startVertexInput.setAlignment(Qt::AlignCenter);
    QFont vertexInputFont;
    vertexInputFont.setFamily("Courier New");
    vertexInputFont.setPixelSize(20);
    startVertexInput.setFixedHeight(30);
    startVertexInput.setFont(vertexInputFont);
    connect(&startVertexInput, &QLineEdit::textChanged, this, &ControlPanel::startVertexChanged);

    algoOutputLabel.setText("Algorithm output");
    font.setPixelSize(18);
    algoOutputLabel.setFont(font);
    algoOutputLabel.setAlignment(Qt::AlignCenter);

    algoOutput.setReadOnly(true);
    QFont algoOutputFont;
    algoOutputFont.setFamily("Courier New");
    algoOutputFont.setPixelSize(20);
    // algoOutput.setFixedW(30);
    algoOutput.setFixedHeight(400);
    algoOutput.setFont(algoOutputFont);

    grid->addWidget(&label, 0, 0, 1, 6, Qt::AlignTop);

    grid->addWidget(&algoLabel, 1, 0, 1, 2, Qt::AlignTop);
    grid->addWidget(&selector, 1, 2, 1, 4, Qt::AlignTop);

    grid->addWidget(&runButton, 2, 0, 1, 4, Qt::AlignTop);
    grid->addWidget(&stopButton, 2, 4, 1, 2, Qt::AlignTop);

    grid->addWidget(&stepBackwardButton, 3, 0, 1, 3, Qt::AlignTop);
    grid->addWidget(&stepForwardButton, 3, 3, 1, 3, Qt::AlignTop);

    grid->addWidget(&startVertexLabel, 4, 0, 1, 3, Qt::AlignCenter);
    grid->addWidget(&startVertexInput, 4, 3, 1, 3, Qt::AlignCenter);

    grid->addWidget(&algoOutputLabel, 5, 0, 2, 6, Qt::AlignCenter);
    grid->addWidget(&algoOutput, 7, 0, 1, 6, Qt::AlignTop);

    auto* empty = new QLabel;
    grid->addWidget(empty, 8, 0, 1, 6, Qt::AlignTop);
    grid->setSpacing(0);
    // grid.setContentsMargins(0, 0, 0, 0);
    setLayout(grid);
    setFixedWidth(300);
    setContentsMargins(0, 0, 0, 0);
}

}  // namespace dsv::UI
