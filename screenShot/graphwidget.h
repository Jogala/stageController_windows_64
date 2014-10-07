#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

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

#include <QGraphicsView>

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void itemMoved();
    QGraphicsScene *scene;
    void refreshBackground();

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();


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
};

#endif // GRAPHWIDGET_H
