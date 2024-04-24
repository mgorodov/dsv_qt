#include <QApplication>
#include <ui/mainwindow.h>
#include <QFile>

QString loadStyleSheet() {
    QFile file("../../src/static/styles.qss");
    file.open(QFile::ReadOnly);
    return QLatin1String(file.readAll());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString styleSheet = loadStyleSheet();
    app.setStyleSheet(styleSheet);

    dsv::UI::MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
