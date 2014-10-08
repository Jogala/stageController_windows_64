#include "graphwidget.h"



GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0), pToCallingWindow(parent)
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-325, -325, 650, 650);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1.0), qreal(1.0));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Elastic Nodes"));

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(5);
    laserSpot = scene->addEllipse(10,10,20,20,pen);
    laserSpot->setOpacity(0);

}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

#ifndef QT_NO_WHEELEVENT
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    takeScreenShot();

    painter->drawPixmap(scene->sceneRect().x(),scene->sceneRect().y(),pixScreenShot);

}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::addNode()
{
    Node * newNode = new Node(this);

    nodeList.append(newNode);

    scene->addItem(nodeList.last());
    nodeList.last()->setPos(0,0);

    if(nodeList.length()>1)
    {
        Edge * newEdge = new Edge(nodeList[nodeList.length()-2], nodeList.last());
        edgeList.append(newEdge);
        scene->addItem(edgeList.last());
    }

}

void GraphWidget::removeNode()
{
    if(nodeList.length())
    {
        //remove last node from scene
        scene->removeItem(nodeList.last());
        //remove last node from nodeList
        nodeList.removeLast();
    }

    if(edgeList.length())
    {
        scene->removeItem(edgeList.last());
        edgeList.removeLast();
    }
}

void GraphWidget::polygonZugSaveCoordinates()
{
    std::cout<<"void GraphWidget::polygonZugSaveCoordinates() ENTERING"<<std::endl;

    loadUFaktoren();

    std::string fileName = "./cut_coords/polygonZugCoord.txt";
    std::fstream f;
    f.open(fileName, std::fstream::out | std::fstream::trunc);

    for(Node* item : nodeList)
    {
        f<<100+uFaktorX*(item->pos().x()+::gE545.itsLaserPosX)<<"\t"<<100-uFaktorY*(item->pos().y()-::gE545.itsLaserPosY)<<"\t"<<100<<std::endl;

        std::cout<<100+uFaktorX*(item->pos().x()+::gE545.itsLaserPosX)<<" "<<100-uFaktorY*(item->pos().y()-::gE545.itsLaserPosY)<<std::endl;
    }

    f.close();

    std::cout<<"void GraphWidget::polygonZugSaveCoordinates() LEAVING"<<std::endl;
}

void GraphWidget::addLaserSpotToScene()
{
    std::cout<<"void GraphWidget::addLaserSpotToScene() ENTERING"<<std::endl;

    ::gE545.loadLaserPosValuesFromFile();
    laserSpot->setPos(::gE545.itsLaserPosX,::gE545.itsLaserPosY);
    laserSpot->setOpacity(1);
    laserSpot->setFlag(QGraphicsItem::ItemIsMovable);
    laserSpot->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    laserSpot->setEnabled(1);

    std::cout<<"void GraphWidget::addLaserSpotToScene() LEAVING"<<std::endl;
}

void GraphWidget::writePosOfLaserSpotToFile_then_removeLaserSpotFromScene()
{
    std::cout<<"void GraphWidget::writePosOfLaserSpotToFile_then_removeLaserSpotFromScene() ENTERING"<<std::endl;

    ::gE545.itsLaserPosX = laserSpot->pos().x();
    ::gE545.itsLaserPosY = laserSpot->pos().y();
    gE545.writeLaserPosValuesToFile();

    laserSpot->setOpacity(0);
    laserSpot->setEnabled(0);

    std::cout<<"void GraphWidget::writePosOfLaserSpotToFile_then_removeLaserSpotFromScene() LEAVING"<<std::endl;
}

void GraphWidget::takeScreenShot()
{
    geomScreenShot.setRect(2300,200, 650,650);
    pToCallingWindow->setWindowOpacity(0);

    QScreen *screen = QGuiApplication::primaryScreen();

    //Take the screenshot using the geometry of the screen
    pixScreenShot = screen->grabWindow(0, geomScreenShot.x(), geomScreenShot.y(), geomScreenShot.width(), geomScreenShot.height());

    pToCallingWindow->setWindowOpacity(1);
}

void GraphWidget::loadUFaktoren()
{
    std::cout<<"load Umrechungsfaktoren Image zu real Coordinates  START"<<std::endl;
    std::string fileName = "./Stored_Values/uFaktoren.txt";
    std::fstream f;
    f.open(fileName, std::fstream::in);
    f>>uFaktorX;
    f>>uFaktorY;
    f.close();
    std::cout<<"load Umrechungsfaktoren Image zu real Coordinates  DONE"<<std::endl;
}

void GraphWidget::refreshBackground()
{
    takeScreenShot();
    QBrush brush(pixScreenShot);
    scene->setBackgroundBrush(brush);

}
