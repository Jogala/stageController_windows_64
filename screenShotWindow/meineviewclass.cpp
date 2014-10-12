#include "meineviewclass.h"
#include "malkasten.h"
#include <QDebug>


meineViewClass::meineViewClass(MeineSceneClass *pToScene, Malkasten * pToCallingMalkasten) :
    QGraphicsView(pToScene), pToMalkasten(pToCallingMalkasten), scene(pToScene)
{
    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}

void meineViewClass::enableDrawFreeHand(bool val)
{
    drawFreehand = val;
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
            Node * newNode = new Node;

            scene->nodeFreeHandList.append(newNode);

            scene->addItem(scene->nodeFreeHandList.last());
            scene->nodeFreeHandList.last()->setPos(coord.x(),coord.y());

            if(scene->nodeFreeHandList.length()>1)
            {
                std::cout<<"edge gets added"<<std::endl;
                Edge * newEdge = new Edge(scene->nodeFreeHandList[scene->nodeFreeHandList.length()-2], scene->nodeFreeHandList.last());
                scene->edgeFreeHandList.append(newEdge);
                scene->addItem(scene->edgeFreeHandList.last());
                std::cout<<"edge got added"<<std::endl;
            }
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
