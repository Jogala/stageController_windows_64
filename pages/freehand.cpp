#include "freehand.h"
#include "ui_freehand.h"

#include <QDebug>

freeHand::freeHand(QWidget *parent,Malkasten * pToMainWindowsMalkasten) :
    QWidget(parent),mMalkasten(pToMainWindowsMalkasten), ui(new Ui::freeHand)
{
    ui->setupUi(this);
    qDebug()<<mMalkasten->height();

    mMalkasten->view->enableDrawFreeHand(ui->radioButton->isChecked());

    ui->spinBox_screenShot_x->setMinimum(0);
    ui->spinBox_screenShot_x->setMaximum(5000);
    ui->spinBox_screenShot_y->setMinimum(0);
    ui->spinBox_screenShot_y->setMaximum(5000);
    ui->spinBox_screenShot_w->setMinimum(1);
    ui->spinBox_screenShot_w->setMaximum(5000);
    ui->spinBox_screenShot_h->setMinimum(1);
    ui->spinBox_screenShot_h->setMaximum(5000);

    loadScreenShotGeometry();
    loadUFactors();

    mMalkasten->refreshBackground();
}

freeHand::~freeHand()
{
    delete ui;
}

void freeHand::on_radioButton_clicked(bool checked)
{
    mMalkasten->view->enableDrawFreeHand(checked);
}

void freeHand::on_pushButton_refreshBackground_clicked()
{
    mMalkasten->refreshBackground();
}
void freeHand::on_spinBox_screenShot_x_editingFinished()
{
    mMalkasten->recScreenShot.setX(ui->spinBox_screenShot_x->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();

}
void freeHand::on_spinBox_screenShot_y_editingFinished()
{
    mMalkasten->recScreenShot.setY(ui->spinBox_screenShot_y->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();

}
void freeHand::on_spinBox_screenShot_w_editingFinished()
{
    mMalkasten->recScreenShot.setWidth(ui->spinBox_screenShot_w->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();

}
void freeHand::on_spinBox_screenShot_h_editingFinished()
{
    mMalkasten->recScreenShot.setHeight(ui->spinBox_screenShot_h->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();

}

void freeHand::loadScreenShotGeometry()
{

    std::string storedValuesPath = "./Stored_Values/screenshot.txt";
    double x;
    double y;
    double w;
    double h;

    std::cout<<"void GraphWidget::loadScreenShotGeometry(QRect geom) ENTERING"<<std::endl;

    std::fstream f;
    f.open(storedValuesPath);

    if (f.is_open()) {

        f>>x;
        f>>y;
        f>>w;
        f>>h;
    }
    f.close();

    mMalkasten->recScreenShot.setRect(x,y,w,h);

    ui->spinBox_screenShot_x->setValue(x);
    ui->spinBox_screenShot_y->setValue(y);
    ui->spinBox_screenShot_w->setValue(w);
    ui->spinBox_screenShot_h->setValue(h);

    std::cout<<"void GraphWidget::loadScreenShotGeometry(QRect geom) LEAVING"<<std::endl;
}
void freeHand::saveScreenShotGeometry()
{

    std::string storedValuesPath = "./Stored_Values/screenshot.txt";
    std::fstream f;
    f.open(storedValuesPath);

    if (f.is_open()) {

        f<<ui->spinBox_screenShot_x->value()<<std::endl;
        f<<ui->spinBox_screenShot_y->value()<<std::endl;
        f<<ui->spinBox_screenShot_w->value()<<std::endl;
        f<<ui->spinBox_screenShot_h->value()<<std::endl;
    }
    f.close();
}

void freeHand::loadUFactors()
{

    std::string storedValuesPath = "./Stored_Values/uFactors.txt";

    double uFac;
    std::fstream f;
    f.open(storedValuesPath);

    if (f.is_open()) {

        f>>uFac;

    }
    f.close();

    mMalkasten->scene->uFaktorFromSceneToStage = uFac;
    ui->doubleSpinBox_uFactor->setValue(uFac);

}
void freeHand::saveUFactors()
{
    std::string storedValuesPath = "./Stored_Values/uFactors.txt";
    std::fstream f;
    f.open(storedValuesPath);

    if (f.is_open()) {

        f<<ui->doubleSpinBox_uFactor->value()<<std::endl;
    }
    f.close();
}

void freeHand::on_pushButton_clear_clicked()
{
    mMalkasten->scene->removeAllNodes();
}

void freeHand::on_pushButton_cut_freeHand_press_clicked()
{
    mMalkasten->scene->writeCoordOfNodesToFile();
}

void freeHand::on_doubleSpinBox_uFactor_editingFinished()
{
    mMalkasten->scene->uFaktorFromSceneToStage = ui->doubleSpinBox_uFactor->value();
    saveUFactors();
}
