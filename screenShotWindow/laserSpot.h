#ifndef LASERSPOT_H
#define LASERSPOT_H

#include <QGraphicsItem>
#include <QObject>
#include <QMouseEvent>
#include <QGraphicsSceneMoveEvent>
#include <QPoint>
#include <QDebug>
#include <QPaintEvent>
#include <QGraphicsScene>

class LaserSpot : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit LaserSpot(QGraphicsScene *parent = 0);

    double posOfCenterX();
    double posOfCenterY();

signals:
    void notification();

public slots:

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
};

#endif // LASERSPOT_H
