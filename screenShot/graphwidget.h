#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsItem>
#include <QCoreApplication>
#include <QGraphicsView>
#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <QImage>
#include <QDebug>
#include <QScreen>

#include <QKeyEvent>
#include <QList>
#include <math.h>
#include <fstream>

#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include "globalstagecontroller.h"

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void itemMoved();
    QGraphicsScene *scene;
    void refreshBackground();
    QList <Node*> nodeList;
    QList <Edge*> edgeList;
    QGraphicsEllipseItem * laserSpot;

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();
    void addNode();
    void removeNode();
    void polygonZugSaveCoordinates();
    void addLaserSpotToScene();
    void writePosOfLaserSpotToFile_then_removeLaserSpotFromScene();

protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event);
#endif
    void drawBackground(QPainter *painter, const QRectF &rect);

    void scaleView(qreal scaleFactor);

    void takeScreenShot();

private:
    int timerId;
    Node *centerNode;
    QWidget * pToCallingWindow;
    QRect geomScreenShot;
    QPixmap pixScreenShot;

    double uFaktorX=1;
    double uFaktorY=1;

};

#endif // GRAPHWIDGET_H
