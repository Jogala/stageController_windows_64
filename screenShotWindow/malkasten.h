#ifndef MALKASTEN_H
#define MALKASTEN_H

#include <QObject>
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
#include <iostream>
#include <fstream>
#include "meinesceneclass.h"
#include "meineviewclass.h"


class Malkasten : public QWidget
{
    Q_OBJECT
public:
    explicit Malkasten(QWidget *parent = 0);
    ~Malkasten();

    MeineSceneClass *scene;
    meineViewClass* view;

    void takeScreenShot();
    QPixmap * pixScreenShot;
    //gets values assigned by loadScreenShotGeometry()
    QRect recScreenShot;

public slots:
     void refreshBackground();

protected:



signals:



private:


    QRect fensterSizeAndPos;




};

#endif // MALKASTEN_H
