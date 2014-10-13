#ifndef METERSTAB_H
#define METERSTAB_H

#include <QGraphicsLineItem>
#include <QObject>
#include <QDebug>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMoveEvent>
#include <QDebug>
#include <QPaintEvent>
#include <QGraphicsScene>

class Meterstab : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit Meterstab(QObject *parent = 0);

signals:
    void notification();

public slots:

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
};


#endif // METERSTAB_H
