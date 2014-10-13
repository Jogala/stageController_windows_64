#include "meterstab.h"

Meterstab::Meterstab(QObject *parent)
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    this->setPen(QPen(Qt::red,5));
    this->setLine(100,100,300,100);
}

void Meterstab::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void Meterstab::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void Meterstab::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

QVariant Meterstab::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        qDebug()<<"in itemChange";
        emit this->notification();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
