#include "static.h"

#include <QDebug>
#include <QFile>
#include <QIcon>
#include <QPainter>

namespace dsv::Static {

QString loadResource(const QString& resourcePath) {
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Resource by path " << resourcePath << " is not found" << Qt::endl;
        return "";
    }
    return file.readAll();
}

QPixmap loadPixmap(const QString& resourcePath, const QSize& size, const QColor& color) {
    auto pixmap = QIcon(resourcePath).pixmap(size);

    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.setBrush(color);
    painter.setPen(color);
    painter.drawRect(pixmap.rect());

    return pixmap;
}

}  // namespace dsv::Static
