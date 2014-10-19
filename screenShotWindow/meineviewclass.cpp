#include "meineviewclass.h"
#include "malkasten.h"
#include <QDebug>


meineViewClass::meineViewClass(MeineSceneClass *pToScene, Malkasten * pToCallingMalkasten) :
    QGraphicsView(pToScene), pToMalkasten(pToCallingMalkasten), scene(pToScene)
{
    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}

void meineViewClass::enableDrawPulses(bool val)
{
    drawPulses = val;

    if(val)
    {
        drawFreehand = 0;
    }
}

void meineViewClass::enableDrawFreeHand(bool val)
{
    drawFreehand = val;

    if(val)
    {
        drawPulses = 0;
    }

}

void meineViewClass::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    qDebug()<<"maus klicked";

    if(event->button()==Qt::LeftButton)
    {
        QPointF coord = mapToScene(event->pos());

        if(drawFreehand)
        {
            scene->addNode(coord);
        }

        if(drawPulses)
        {
            scene->addPuls(coord);
        }
    }
}

void meineViewClass::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void meineViewClass::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}
