#ifndef MEINESCENECLASS_H
#define MEINESCENECLASS_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QPen>
#include <QColor>
#include <QScreen>
#include <QGuiApplication>
#include <QLayout>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <iostream>
#include <fstream>

#include "node.h"
#include "edge.h"


class Malkasten;

class MeineSceneClass : public QGraphicsScene
{
public:
    MeineSceneClass(QObject *parent = 0,Malkasten * pToCallingMalkasten = 0);

    void setNewBackgroundPixmap(QPixmap * pToPix);

    void removeAllNodes();
    void writeCoordOfNodesToFile();
    int uFaktorFromSceneToStage;
    QList <Node*> nodeFreeHandList;
    QList <Edge*> edgeFreeHandList;


public slots:

private:
    Malkasten * pToMalkasten;
    QGraphicsPixmapItem * backGroundItem;


};

#endif // MEINESCENECLASS_H
