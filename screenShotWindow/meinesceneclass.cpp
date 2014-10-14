#include "meinesceneclass.h"
#include "malkasten.h"
#include "globalstagecontroller.h"
#include "pages/Einstellungen.h"

#include <QtGui>
#include <QGraphicsSceneMouseEvent>

MeineSceneClass::MeineSceneClass(QObject *parent, Malkasten * pToCallingMalkasten)
    :QGraphicsScene(parent)
{   
    pToCallingMalkasten->takeScreenShot();
    backGroundItem = this->addPixmap(*pToCallingMalkasten->pixScreenShot);
    backGroundItem->setZValue(-1);

    laserSpot = new LaserSpot(this);
    laserSpot->setBrush(Qt::red);
    laserSpot->setEnabled(1);
    gE545.loadLaserPosValuesFromFile();
    laserSpot->setRect(0,0,10,10);
    laserSpot->moveBy(::gE545.itsLaserPosX,::gE545.itsLaserPosY);
    this->addItem(laserSpot);
    laserSpot->hide();


    blueLaserSpot = new LaserSpot(this);
    blueLaserSpot->setBrush(Qt::darkCyan);
    blueLaserSpot->setEnabled(1);
    blueLaserSpot->setRect(0,0,10,10);
    this->addItem(blueLaserSpot);
    blueLaserSpot->hide();

    meterstab = new Meterstab;
    this->addItem(meterstab);
    meterstab->hide();


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

bool MeineSceneClass::removeLastNode()
{
    if(nodeFreeHandList.length())
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

    return nodeFreeHandList.length();

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

void MeineSceneClass::giveItAPointerToSettingsPage(Einstellungen * pToSettingsPage)
{
    settingsPageWidget = pToSettingsPage;
    connect(laserSpot,SIGNAL(notification()),settingsPageWidget,SLOT(assignNewValuesToLaserPos()));
    connect(meterstab,SIGNAL(notification()),settingsPageWidget,SLOT(assignNewValuesToSpinBoxLineLength()));

}


