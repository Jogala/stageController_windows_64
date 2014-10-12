#include "malkasten.h"
#include <QDebug>
#include <QRectF>
#include <QGraphicsItem>


Malkasten::Malkasten(QWidget *parent) :
     fensterSizeAndPos(100,100,600,600)
{
    this->setAttribute( Qt::WA_QuitOnClose, false );
    this->setGeometry(fensterSizeAndPos);

    pixScreenShot =  new QPixmap;
    scene= new MeineSceneClass(0,this);
    view = new meineViewClass(scene,this);

    QGraphicsEllipseItem *eli = scene->addEllipse(0,0,10,10,QPen(Qt::blue,5),QBrush(Qt::red));
    eli->setFlag(QGraphicsItem::ItemIsMovable);
    eli->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    eli->setEnabled(1);

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addWidget(view);

    takeScreenShot();

    view->show();

    qDebug()<<view->geometry();
    qDebug()<<scene->sceneRect();

    view->setMouseTracking(true);
}

Malkasten::~Malkasten()
{
    qDebug()<<"destructor called on Malkasten";
    this->destroy(1,1);
}

void Malkasten::takeScreenShot()
{
this->setWindowOpacity(0);

QScreen *screen = QGuiApplication::primaryScreen();

//Take the screenshot using the geometry of the screen
*pixScreenShot = screen->grabWindow(0, recScreenShot.x(), recScreenShot.y(), recScreenShot.width(), recScreenShot.height());

this->setWindowOpacity(1);
}

void Malkasten::refreshBackground()
{
    //assigns new pixmap to pixScreenShot
    takeScreenShot();
    //scene has access to pixScreenShot
    scene->setNewBackgroundPixmap(pixScreenShot);
}
