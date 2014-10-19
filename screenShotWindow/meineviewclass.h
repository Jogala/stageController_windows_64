#ifndef MEINEVIEWCLASS_H
#define MEINEVIEWCLASS_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QRect>
#include <QPen>
#include <QColor>
#include <QScreen>
#include <QList>
#include "meinesceneclass.h"
#include "node.h"
#include "edge.h"

class Malkasten;

class meineViewClass : public QGraphicsView
{
    Q_OBJECT
public:
    explicit meineViewClass(MeineSceneClass *pToScene = 0, Malkasten * pToCallingMalkasten=0);

signals:

public slots:

public:
    bool drawFreehand = 0;
    bool drawPulses = 0;

    void enableDrawPulses(bool );
    void enableDrawFreeHand(bool );

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

private:
    Malkasten* pToMalkasten;

    QPoint jetzigerPunkt;
    QPoint vorhergegangenerPunkt;
    MeineSceneClass *scene;


};

#endif // MEINEVIEWCLASS_H
