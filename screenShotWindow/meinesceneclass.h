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
    void addPulse(QPointF coordWhereToPutNewPuls);
    void removeAllPulses();
    bool removeLastPulse();

    void addNode(QPointF coordWhereToPutNewNode);
    void removeAllNodes();
    bool removeLastNode();
    void writeCoordOfNodesToFile();

    QList <Node*> nodeFreeHandList;
    QList <Edge*> edgeFreeHandList;
    QList <Node*> nodePulsList;

    LaserSpot * laserSpot;
    LaserSpot * greenLaserSpot;
    LaserSpot * figuresLaserSpot;
    Node *punkt;

    //variables need for conversion pixel to real length
    Meterstab *meterstab;
    double uFactorFromSceneToStage;

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
