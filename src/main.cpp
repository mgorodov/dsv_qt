#include <QApplication>
#include <ui/mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    dsv::UI::MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
