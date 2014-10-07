#include "screenshotwin.h"
#include "ui_screenshotwin.h"

screenShotWin::screenShotWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::screenShotWin)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    QPen pen(Qt::black);
    pen.setWidth(10);

    myPixmap = new QPixmap(256,256);
    QImage im;
    im.load("icon.png");

    QPixmap preview;
    preview.convertFromImage(im);

    scene->addPixmap(preview);
    //selectedArea = scene->addRect(selectedArea_leftTopCorner.x(),selectedArea_leftTopCorner.y(),selectedArea_width, selectedArea_height,pen);
    //selectedArea ->hide();
}

screenShotWin::~screenShotWin()
{
    delete ui;
}

void screenShotWin::setSelectedArea_Geometry(QPoint leftP, int width, int height)
{
//    selectedArea_leftTopCorner.setX(leftP.x());
//    selectedArea_leftTopCorner.setY(leftP.y());
//    selectedArea_width=width;
//    selectedArea_height=height;
}

void screenShotWin::selectedArea_actualize()
{
//    selectedArea->setPos(selectedArea_leftTopCorner.x(),selectedArea_leftTopCorner.y());
//    scene->update();
}

void screenShotWin::selectedArea_hide()
{
//    selectedArea->hide();
}

void screenShotWin::selectedArea_show()
{
}

void screenShotWin::takeScreenShotAndDisplayIt()
{
//    this->setWindowOpacity(0);
//    QRect rect(screenShotX,screenShotY, screenShotW, screenShotH);

//    QDesktopWidget * desktop = QApplication::desktop();
//    myPixmap->grabWindow( QApplication::desktop()->winId(),desktop->x(),desktop->y(), desktop->width(),desktop->height());
//    *myPixmap = myPixmap->copy(rect);
//    scene->addPixmap(*myPixmap);
//    scene->update();

//    this->setWindowOpacity(1);
}

void screenShotWin::setScreenShot_Geometry(int x, int y, int w, int h)
{

    screenShotX=x;
    screenShotY=y;
    screenShotH=h;
    screenShotW=w;

}

void screenShotWin::mousePressEvent(QMouseEvent *event)
{

}

