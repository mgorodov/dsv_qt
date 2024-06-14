#pragma once

#include <misc/algorithm_action.h>
#include <misc/Observer.h>

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>

namespace dsv::UI {

class ControlPanel : public QGroupBox {
    Q_OBJECT
    using AlgoData = std::optional<AlgorithmAction>;
    using ObservableAlgoData = NSLibrary::CObservableDataMono<AlgoData>;
    using ObserverAlgoData = NSLibrary::CObserver<AlgoData>;

public:
    explicit ControlPanel(QWidget* parent = nullptr);
    void subscribeToAlgoData(ObserverAlgoData* observer);

private slots:
    void runClicked();
    void stopClicked();
    void backwardClicked();
    void forwardClicked();
    void algoChanged(size_t index);
    void startVertexChanged(const QString& text);

private:
    void createLayout();

    QLabel label;
    QLabel algoLabel;
    QComboBox selector;
    QPushButton runButton;
    QPushButton stopButton;
    QPushButton stepBackwardButton;
    QPushButton stepForwardButton;
    QLabel startVertexLabel;
    QLineEdit startVertexInput;
    QLabel algoOutputLabel;
    QPlainTextEdit algoOutput;

    EAlgorithm currentAlgorithm_;
    size_t startVertex_{0};

    ObservableAlgoData algoDataOutPort_;
};

}  // namespace dsv::UI
