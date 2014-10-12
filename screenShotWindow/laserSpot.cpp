#include "laserSpot.h"
#include <QDebug>

LaserSpot::LaserSpot(QGraphicsScene *parent) :
    QObject (parent)
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void LaserSpot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant LaserSpot::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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
