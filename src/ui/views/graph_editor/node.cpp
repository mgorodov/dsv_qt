#include "node.h"

#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QVector2D>

namespace dsv::UI {

qreal Node::maxZValue_ = 0;
int Node::recursionDepth_ = 0;

Node::Node(const QString &text, const qreal radius)
    : text_(text),
      radius_(radius),
      defaultColor_(Qt::white),
      currentColor_(defaultColor_),
      pressedColor_(defaultColor_.darker(180)) {
    setFlags(ItemIsMovable | ItemSendsGeometryChanges);
}

QRectF Node::boundingRect() const {
    return QRectF(-50, -50, radius_, radius_);
}

QRectF Node::textRect() const {
    return QRectF(-(50 + radius_ * 0.2), -(50 + radius_ * 0.2), radius_ * 1.4, radius_ * 1.4);
}

int Node::getRadius() {
    return radius_;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(currentColor_);
    painter->setPen(Qt::black);
    painter->drawEllipse(-50, -50, radius_, radius_);
    painter->drawText(textRect(), Qt::AlignCenter, text_);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        emit positionChanged();
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();

        QRectF newRect = QRectF(
            newPos.x() + boundingRect().left(), newPos.y() + boundingRect().top(), boundingRect().width(),
            boundingRect().height()
        );

        if (!rect.contains(newRect)) {
            if (newRect.left() < rect.left()) {
                newPos.setX(rect.left() - boundingRect().left());
            } else if (newRect.right() > rect.right()) {
                newPos.setX(rect.right() - boundingRect().right());
            }

            if (newRect.top() < rect.top()) {
                newPos.setY(rect.top() - boundingRect().top());
            } else if (newRect.bottom() > rect.bottom()) {
                newPos.setY(rect.bottom() - boundingRect().bottom());
            }

            return newPos;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragStartPos_ = event->pos();
        ++maxZValue_;
        setZValue(maxZValue_);
        currentColor_ = pressedColor_;
        update();
    }
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);
    pushOtherNodes();
}

void Node::pushOtherNodes() {
    QList<QGraphicsItem *> collidingItemsList = collidingItems();

    for (QGraphicsItem *currentItem : collidingItemsList) {
        Node *collidedNode = dynamic_cast<Node *>(currentItem);
        if (collidedNode) {
            QVector2D direction(collidedNode->pos() - pos());
            if (!direction.isNull()) {
                direction.normalize();

                qreal pushDistance = 10;
                QPointF pushVector = direction.toPointF() * pushDistance;
                collidedNode->setPos(collidedNode->pos() + pushVector);
            }
            QRectF rect = scene()->sceneRect();
            QPointF newPos = collidedNode->pos();
            QRectF newRect = collidedNode->boundingRect().translated(newPos);
            if (!rect.contains(newRect)) {
                collidedNode->setPos(collidedNode->sceneBoundingRect().intersected(rect).topLeft());
            }
            recursionDepth_ += 1;
            if (recursionDepth_ < 1000) {
                collidedNode->pushOtherNodes();
            } else {
                recursionDepth_ = 0;
                return;
            }
        }
    }
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    currentColor_ = defaultColor_;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    bool ok;
    QString newText =
        QInputDialog::getText(nullptr, "Edit Node", "Enter new node value", QLineEdit::Normal, text_, &ok);
    if (ok && !newText.isEmpty()) {
        text_ = newText;
        update();
    }
}

}  // namespace dsv::UI
