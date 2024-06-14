#pragma once
#include <QPixmap>
#include <QString>

namespace dsv::Static {

QString loadResource(const QString& resourcePath);
QPixmap loadPixmap(const QString& resourcePath, const QSize& size, const QColor& color);

}  // namespace dsv::Static
