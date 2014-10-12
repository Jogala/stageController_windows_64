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


class Malkasten;
class settingsPage;

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

    void giveItAPointerToSettingsPage(settingsPage * );

public slots:
    void printHallo(){
        qDebug()<<"hallo";
    }

signals:


private:
    Malkasten * pToMalkasten;
    QGraphicsPixmapItem * backGroundItem;
    settingsPage * settingsPageWidget;



};

#endif // MEINESCENECLASS_H