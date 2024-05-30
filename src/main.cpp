#include <application/application.h>
#include <misc/QRunTime.h>

int main(int argc, char *argv[]) {
    QRunTime qtRuntime(argc, argv);
    dsv::Application app;
    app.show();
    return qtRuntime.exec();
}
