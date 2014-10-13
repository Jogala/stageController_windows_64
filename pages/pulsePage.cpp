#include "pulsePage.h"
#include "ui_pulsePage.h"

pulsePage::pulsePage(QWidget *parent,  Malkasten * pToMainWindowsMalkasten) :
    QWidget(parent),mMalkasten(pToMainWindowsMalkasten), scene(pToMainWindowsMalkasten->scene),ui(new Ui::pulsePage)
{
    std::cout<<"pulsePage::pulsePage(QWidget *parent) ENTERING"<<std::endl;

    ui->setupUi(this);
    ui->T_spinBox->setMinimum(0);
    ui->T_spinBox->setMaximum(10000);
    ui->minDeltaT_spinBox->setMinimum(0);
    ui->minDeltaT_spinBox->setMaximum(10000);

    ui->T_spinBox->setValue(200);

    ui->groupBox_blueLaserSpot->setEnabled(0);

    std::cout<<"pulsePage::pulsePage(QWidget *parent) LEAVING"<<std::endl;
}

pulsePage::~pulsePage()
{
    delete ui;
}

void pulsePage::on_open_shutter_clicked()
{
    gE545.openShutter();
}


void pulsePage::on_close_shutter_clicked()
{
    gE545.closeShutter();
}


void pulsePage::on_pulse_button_clicked()
{
   double shutterOpenTime = ui->T_spinBox->value();
   double minShutterClosedTime = ui->minDeltaT_spinBox->value();

   if (gE545.checkIfAnyLimit()){
       gE545.closeShutter();
       QThread::msleep(shutterOpenTime);
       gE545.openShutter();
   }
   else
   {
       gE545.openShutter();
       QThread::msleep(shutterOpenTime);
       gE545.closeShutter();
   }

   QThread::msleep(minShutterClosedTime);

   mMalkasten->refreshBackground();
}

void pulsePage::on_pushButton_refreshBackground_clicked()
{
    mMalkasten->refreshBackground();
}


void pulsePage::on_open_shutter__blueDot_clicked()
{
    gE545.openShutter();
}

void pulsePage::on_close_shutter___blueDot_clicked()
{
     gE545.closeShutter();
     ::gE545.moveTo(100,100,100);
}

void pulsePage::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
         scene->blueLaserSpot->show();
         ui->groupBox_blueLaserSpot->setEnabled(1);
    }else
    {
         scene->blueLaserSpot->hide();
         ui->groupBox_blueLaserSpot->setEnabled(0);
    }
}

void pulsePage::on_pulse_button___blueDot_clicked()
{
    double shutterOpenTime = ui->T_spinBox->value();
    double minShutterClosedTime = ui->minDeltaT_spinBox->value();


    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

    gE545.printVelocity();
    ::gE545.printPosition();

    std::cout<<"##################################################################################################"<<std::endl;
    std::cout<<"##################################################################################################"<<std::endl;
    std::cout<<scene->uFaktorFromSceneToStage*(scene->blueLaserSpot->x()- scene->laserSpot->x())<<std::endl;
    std::cout<<scene->uFaktorFromSceneToStage*(scene->blueLaserSpot->y()- scene->laserSpot->y())<<std::endl;
    std::cout<<"##################################################################################################"<<std::endl;
    std::cout<<"##################################################################################################"<<std::endl;


    gE545.moveTo(
                    100+scene->uFaktorFromSceneToStage*(scene->blueLaserSpot->x()- scene->laserSpot->x()),
                    100-scene->uFaktorFromSceneToStage*(scene->blueLaserSpot->y()- scene->laserSpot->y()),
                    100
                 );
    ::gE545.printPosition();

    if (gE545.checkIfAnyLimit()){
        gE545.closeShutter();
        QThread::msleep(shutterOpenTime);
        gE545.openShutter();
    }
    else
    {
        gE545.openShutter();
        QThread::msleep(shutterOpenTime);
        gE545.closeShutter();
    }

    QThread::msleep(minShutterClosedTime);
    gE545.moveTo(100,100,100);
    mMalkasten->refreshBackground();
}
