#pragma once

#include <QApplication>

class QRunTime : public QApplication {
public:
    QRunTime(int& argc, char** argv);

private:
    bool eventFilter(QObject* obj, QEvent* event) override;
};
