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

    ui->groupBox_greenLaserSpot->setEnabled(0);

    ui->checkBox_thunderstorm->setChecked(0);

    //Set Shortcut
    QShortcut *refreshBackground = new QShortcut(QKeySequence("R"), this);
    QObject::connect(refreshBackground, SIGNAL(activated()), mMalkasten, SLOT(refreshBackground()));

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
         scene->greenLaserSpot->show();
         ui->groupBox_greenLaserSpot->setEnabled(1);
    }else
    {
         scene->greenLaserSpot->hide();
         ui->groupBox_greenLaserSpot->setEnabled(0);
    }
}

void pulsePage::on_pulse_button___blueDot_clicked()
{
    double shutterOpenTime = ui->T_spinBox->value();
    double minShutterClosedTime = ui->minDeltaT_spinBox->value();

    gE545.moveTo(
                    100+scene->uFactorFromSceneToStage*(scene->greenLaserSpot->posOfCenterX()- scene->laserSpot->posOfCenterX()),
                    100-scene->uFactorFromSceneToStage*(scene->greenLaserSpot->posOfCenterY()- scene->laserSpot->posOfCenterY()),
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


void pulsePage::on_checkBox_thunderstorm_clicked(bool checked)
{
    mMalkasten->view->enableDrawPulses(checked);
}

void pulsePage::on_open_shutter__blueDot_2_clicked()
{
    double uFactorFromSceneToStage = scene->uFactorFromSceneToStage;

    double shutterOpenTime = ui->T_spinBox->value();
    ::gE545.setVelocity(9000,9000,9000);

    LaserSpot * laserSpot = scene->laserSpot;

    for(Node *item : scene->nodePulsList)
    {


        ::gE545.moveTo
                (
                    100+uFactorFromSceneToStage*(item->pos().x()-0.5*item->boundingRect().width()-laserSpot->pos().x()),
                    100-uFactorFromSceneToStage*(item->pos().y()-0.5*item->boundingRect().height()-laserSpot->pos().y()),
                    100
                );

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

    }

    ::gE545.moveTo(100,100,100);


}

void pulsePage::on_pushButton_removeAllPulses_clicked()
{
    scene->removeAllPulses();
}

void pulsePage::on_pushButton_removeLastPulse_clicked()
{

    scene->removeLastPulse();

}

