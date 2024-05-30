#pragma once

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QObject>
#include <QPainter>

namespace dsv::UI {

class Node : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    Node(const QString &text = "Value", const qreal radius = 50);

    QRectF boundingRect() const override;
    QRectF textRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    int getRadius();

    void pushOtherNodes();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void positionChanged();
    void ValueChanged();

private:
    static qreal maxZValue_;
    static int recursionDepth_;

    int radius_;
    QString text_;
    QPointF dragStartPos_;
    QColor defaultColor_;
    QColor currentColor_;
    QColor pressedColor_;
};

}  // namespace dsv::UI
