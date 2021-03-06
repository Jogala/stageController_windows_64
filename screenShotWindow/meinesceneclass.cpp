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


    greenLaserSpot = new LaserSpot(this);
    greenLaserSpot->setBrush(Qt::green);
    greenLaserSpot->setEnabled(1);
    greenLaserSpot->setRect(0,0,10,10);
    this->addItem(greenLaserSpot);
    greenLaserSpot->hide();

    figuresLaserSpot = new LaserSpot(this);
    figuresLaserSpot->setBrush(Qt::white);
    figuresLaserSpot->setEnabled(1);
    figuresLaserSpot->setRect(0,0,10,10);
    this->addItem(figuresLaserSpot);

    meterstab = new Meterstab;
    this->addItem(meterstab);
    meterstab->hide();

}

void MeineSceneClass::setNewBackgroundPixmap(QPixmap * pToPix)
{
    backGroundItem->setPixmap(*pToPix);
}

void MeineSceneClass::addPulse(QPointF coordWhereToPutNewPuls)
{

    Node * newNode = new Node;

    //display new bounding rect at tip of the mouse arrow
    coordWhereToPutNewPuls.setX(coordWhereToPutNewPuls.x()+0.5*newNode->boundingRect().height());
    coordWhereToPutNewPuls.setY(coordWhereToPutNewPuls.y()+0.5*newNode->boundingRect().height());

    nodePulsList.append(newNode);

    addItem(nodePulsList.last());
    nodePulsList.last()->setPos(coordWhereToPutNewPuls.x(),coordWhereToPutNewPuls.y());

}

void MeineSceneClass::removeAllPulses()
{
    while(nodePulsList.length())
    {
        //remove last node from scene
        this->removeItem(nodePulsList.last());
        //remove last node from nodeList
        nodePulsList.removeLast();

    }
}

void MeineSceneClass::addNode(QPointF coordWhereToPutNewNode)
{
    Node * newNode = new Node;

    //display new bounding rect at tip of the mouse arrow
    coordWhereToPutNewNode.setX(coordWhereToPutNewNode.x()+0.5*newNode->boundingRect().height());
    coordWhereToPutNewNode.setY(coordWhereToPutNewNode.y()+0.5*newNode->boundingRect().height());

    nodeFreeHandList.append(newNode);

    addItem(nodeFreeHandList.last());
    nodeFreeHandList.last()->setPos(coordWhereToPutNewNode.x(),coordWhereToPutNewNode.y());

    if(nodeFreeHandList.length()>1)
    {
        std::cout<<"edge gets added"<<std::endl;
        Edge * newEdge = new Edge(nodeFreeHandList[nodeFreeHandList.length()-2], nodeFreeHandList.last());
        edgeFreeHandList.append(newEdge);
        addItem(edgeFreeHandList.last());
        std::cout<<"edge got added"<<std::endl;
    }
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

bool MeineSceneClass::removeLastPulse()
{
    if(nodePulsList.length())
    {
        //remove last node from scene
        this->removeItem(nodePulsList.last());
        //remove last node from nodeList
        nodePulsList.removeLast();
    }

    return nodePulsList.length();

}

void MeineSceneClass::writeCoordOfNodesToFile()
{

        std::string fileName = "./cut_coords/coordFreeHand.txt";
        std::fstream f;
        f.open(fileName, std::fstream::out | std::fstream::trunc);

        for(Node* item : nodeFreeHandList)
        {

            double delta = 0.5*item->boundingRect().width();

            f<<100+uFactorFromSceneToStage*(item->pos().x()-::gE545.itsLaserPosX-delta)<<"\t";
            f<<100-uFactorFromSceneToStage*(item->pos().y()-::gE545.itsLaserPosY-delta)<<"\t";
            f<<100<<std::endl;
        }

        f.close();
}

void MeineSceneClass::giveItAPointerToSettingsPage(Einstellungen * pToSettingsPage)
{
    settingsPageWidget = pToSettingsPage;
    connect(laserSpot,SIGNAL(notification()),settingsPageWidget,SLOT(assignNewValuesToLaserPos()));
    connect(meterstab,SIGNAL(notification()),settingsPageWidget,SLOT(assignNewValuesToSpinBoxLineLength()));

}


