#ifndef NODE_H
#define NODE_H


#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QPainter>
#include <QObject>


class Node : public QObject,  public QGraphicsItem {
    Q_OBJECT
public:
    Node();

    QRectF boundingRect() const override;
    QRectF textRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    // Enable itemChange to track position changes
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

protected:
    // Mouse events
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QString text_;
    QPointF dragStartPos_;
    int radius_;
    static qreal maxZValue_;
    QColor defaultColor_;
    QColor currentColor_;
    QColor pressedColor_;

signals:
    void positionChanged();
};

#endif // NODE_H
