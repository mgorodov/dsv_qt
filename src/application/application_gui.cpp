#include "application_gui.h"

#include <ui/static/static.h>

#include <QFile>

namespace dsv::UI {

ApplicationGUI::ApplicationGUI() {
    mainWindow_.setStyleSheet(Static::loadResource(":/styles.qss"));
    mainWindow_.setWindowTitle("Data structures visualization");
    mainWindow_.setWindowIcon(QIcon(":/icons/graph.png"));
}

MainWindow* ApplicationGUI::getMainWindow() {
    return &mainWindow_;
}

}  // namespace dsv::UI
