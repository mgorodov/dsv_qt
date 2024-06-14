#include "QRunTime.h"

#include "QPorts.h"

QRunTime::QRunTime(int& argc, char** argv) : QApplication(argc, argv) {
    installEventFilter(this);
}

bool QRunTime::eventFilter(QObject* obj, QEvent* event) {
    using Message = NSLibrary::detail::Message;
    if (event->type() == Message::type()) {
        Message* msg = static_cast<Message*>(event);
        if (msg->isAlive())
            msg->receiver()->event(event);
        return true;
    }
    return QApplication::eventFilter(obj, event);
}
