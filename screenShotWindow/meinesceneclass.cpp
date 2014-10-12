#include "meinesceneclass.h"
#include "malkasten.h"
#include "globalstagecontroller.h"
#include "pages/settingsPage.h"

#include <QtGui>
#include <QGraphicsSceneMouseEvent>

MeineSceneClass::MeineSceneClass(QObject *parent, Malkasten * pToCallingMalkasten)
    :QGraphicsScene(parent)
{   
    pToCallingMalkasten->takeScreenShot();
    backGroundItem = this->addPixmap(*pToCallingMalkasten->pixScreenShot);
    backGroundItem->setZValue(-1);

    laserSpot = new QGraphicsEllipseItem;
    laserSpot->setBrush(Qt::red);
    laserSpot->setFlag(QGraphicsItem::ItemIsMovable);
    laserSpot->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    laserSpot->setEnabled(1);
    laserSpot->setRect(::gE545.itsLaserPosX,::gE545.itsLaserPosY,10,10);

}

void MeineSceneClass::setNewBackgroundPixmap(QPixmap * pToPix)
{
    backGroundItem->setPixmap(*pToPix);
}

void MeineSceneClass::removeAllNodes()
{

    while(nodeFreeHandList.length())
    {
        //remove last node from scene
        this->removeItem(nodeFreeHandList.last());
        //remove last node from nodeList
        nodeFreeHandList.removeLast();

        if(edgeFreeHandList.length())
        {
            this->removeItem(edgeFreeHandList.last());
            edgeFreeHandList.removeLast();
        }
    }
}

void MeineSceneClass::writeCoordOfNodesToFile()
{

        std::string fileName = "./cut_coords/coordFreeHand.txt";
        std::fstream f;
        f.open(fileName, std::fstream::out | std::fstream::trunc);

        for(Node* item : nodeFreeHandList)
        {
            f<<100+uFaktorFromSceneToStage*(item->pos().x()+::gE545.itsLaserPosX)<<"\t"<<100-uFaktorFromSceneToStage*(item->pos().y()-::gE545.itsLaserPosY)<<"\t"<<100<<std::endl;

            std::cout<<100+uFaktorFromSceneToStage*(item->pos().x()+::gE545.itsLaserPosX)<<" "<<100-uFaktorFromSceneToStage*(item->pos().y()-::gE545.itsLaserPosY)<<std::endl;
        }

        f.close();

}

void MeineSceneClass::giveItAPointerToSettingsPage(settingsPage * pToSettingsPage)
{
    settingsPageWidget = pToSettingsPage;
}


