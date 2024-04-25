#include "static.h"

#include <QDebug>
#include <QFile>

namespace dsv::Static {

QString loadResource(const QString &resourcePath) {
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Resource by path " << resourcePath << " is not found" << Qt::endl;
        return "";
    }
    return file.readAll();
}

}  // namespace dsv::Static
