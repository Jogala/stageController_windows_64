#include "secondpage.h"
#include "ui_secondpage.h"

secondPage::secondPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::secondPage)
{
    std::cout<<"secondPage::secondPage(QWidget *parent) ENTERING"<<std::endl;

    ui->setupUi(this);
    ui->T_spinBox->setMinimum(0);
    ui->T_spinBox->setMaximum(10000);
    ui->minDeltaT_spinBox->setMinimum(0);
    ui->minDeltaT_spinBox->setMaximum(10000);

    ui->T_spinBox->setValue(200);
    this->setLayout(ui->gridLayout);

    std::cout<<"secondPage::secondPage(QWidget *parent) LEAVING"<<std::endl;
}

secondPage::~secondPage()
{
    delete ui;
}

void secondPage::on_open_shutter_clicked()
{
    gE545.openShutter();
}


void secondPage::on_close_shutter_clicked()
{
    gE545.closeShutter();
}


void secondPage::on_pulse_button_clicked()
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

}
