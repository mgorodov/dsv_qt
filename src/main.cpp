#include <application.h>

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication qtRuntime(argc, argv);
    dsv::Application app;
    app.run();
    return qtRuntime.exec();
}
