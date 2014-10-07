
#ifndef SCREENSHOTWIN_H
#define SCREENSHOTWIN_H

#include "Header.h"
#include <QDialog>
#include <QPixmap>
#include <QtQuick>
#include <QtQuick/QQuickView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include <QApplication>
#include <QDesktopWidget>

namespace Ui {
class screenShotWin;
}

class screenShotWin : public QDialog
{
    Q_OBJECT

public:
    explicit screenShotWin(QWidget *parent = 0);



    std::string storedValuesPath_screenShot = "./Stored_Values/screenshot.txt";
    std::string storedValuesPath_selectedArea = "./Stored_Values/selectedArea.txt";

    void mousePressEvent ( QMouseEvent * event );

    bool setLaserPos = 0;
    bool setTopLeftCorner = 0;
    bool setBottomRightCorner = 0;

    QGraphicsRectItem * selectedArea;
    QPoint selectedArea_leftTopCorner;
    int selectedArea_width = 10;
    int selectedArea_height = 10;

    ~screenShotWin();

    //set geometries first in fourthpage, then use the associated functions.
    void setScreenShot_Geometry(int x, int y, int w, int h);
    void takeScreenShotAndDisplayIt();

    void setSelectedArea_Geometry(QPoint leftP, int width, int height );
    void selectedArea_actualize();
    void selectedArea_hide();
    void selectedArea_show();




private:
    Ui::screenShotWin *ui;
    QPixmap * myPixmap;
    QGraphicsScene* scene;

    int screenShotX = 10;
    int screenShotY = 10;
    int screenShotW = 10;
    int screenShotH = 10;




};

#endif // SCREENSHOTWIN_H
