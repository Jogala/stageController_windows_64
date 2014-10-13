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
#include <QObject>

#include "node.h"
#include "edge.h"
#include "laserSpot.h"
#include "meterstab.h"


class Malkasten;
class Einstellungen;

class MeineSceneClass : public QGraphicsScene
{
    Q_OBJECT

public:
    MeineSceneClass(QObject *parent = 0,Malkasten * pToCallingMalkasten = 0);

    void setNewBackgroundPixmap(QPixmap * pToPix);

    void removeAllNodes();
    void writeCoordOfNodesToFile();
    double uFaktorFromSceneToStage;
    QList <Node*> nodeFreeHandList;
    QList <Edge*> edgeFreeHandList;

    LaserSpot * laserSpot;
    LaserSpot * blueLaserSpot;

    Meterstab *meterstab;

    void giveItAPointerToSettingsPage(Einstellungen * );

public slots:
    void printHallo(){
        qDebug()<<"hallo";
    }

signals:


private:
    Malkasten * pToMalkasten;
    QGraphicsPixmapItem * backGroundItem;
    Einstellungen * settingsPageWidget;



};

#endif // MEINESCENECLASS_H
