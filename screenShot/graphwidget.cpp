#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>

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

    Node *node1 = new Node(this);
    Node *node2 = new Node(this);
    Node *node3 = new Node(this);

    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);

    scene->addItem(new Edge(node1, node2));
    scene->addItem(new Edge(node2, node3));


    node1->setPos(-50, -50);
    node2->setPos(0, -50);
    node3->setPos(50, -50);
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


void GraphWidget::takeScreenShot()
{
    geomScreenShot.setRect(2300,200, 650,650);
    pToCallingWindow->setWindowOpacity(0);

    QScreen *screen = QGuiApplication::primaryScreen();

    //Take the screenshot using the geometry of the screen
    pixScreenShot = screen->grabWindow(0, geomScreenShot.x(), geomScreenShot.y(), geomScreenShot.width(), geomScreenShot.height());

    pToCallingWindow->setWindowOpacity(1);
}

void GraphWidget::refreshBackground()
{
    takeScreenShot();
    QBrush brush(pixScreenShot);
    scene->setBackgroundBrush(brush);

}
