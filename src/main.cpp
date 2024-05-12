#include <application/application.h>
#include <misc/QRunTime.h>

int main(int argc, char *argv[]) {
    QRunTime qtRuntime(argc, argv);
    dsv::Application app;
    app.run();
    return qtRuntime.exec();
}
