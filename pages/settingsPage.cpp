#include "settingsPage.h"
#include "ui_settingsPage.h"
#include <QTime>

settingsPage::settingsPage(QWidget *parent, Malkasten * pToMainWindowsMalkasten) :
    QWidget(parent), mMalkasten(pToMainWindowsMalkasten), ui(new Ui::settingsPage)
{
    std::cout<<std::endl;
    std::cout<<"###########################################################"<<std::endl;
    std::cout<<"###########################################################"<<std::endl;
    std::cout<<"settingsPage::settingsPage(QWidget *parent) ENTERING"<<std::endl;
    ui->setupUi(this);

    double stepSize=1;
    double vel = 1000;

    for(auto item : tare){
        item = 0;
    }

    ui->delayFactor_SpinBox->setValue(::macroDelayFactor);

    ui->x_pos->setReadOnly(true);
    ui->y_pos->setReadOnly(true);

    ui->x_pos->setMinimum(-200);
    ui->x_pos->setMaximum(200);

    ui->y_pos->setMinimum(-200);
    ui->y_pos->setMaximum(200);

    ui->vel_spinBox->setMinimum(0);
    ui->vel_spinBox->setMaximum(9900);

    ui->stepSize_spinBox->setMinimum(0);
    ui->stepSize_spinBox->setMaximum(50);

    ui->deltaX_spinBox->setMinimum(-200);
    ui->deltaX_spinBox->setMaximum(200);

    ui->deltaY_spinBox->setMinimum(-200);
    ui->deltaY_spinBox->setMaximum(200);

    gE545.getPositon(pos);
    ui->x_pos->setValue(pos[0]);
    ui->y_pos->setValue(pos[1]);


    gE545.setVelocity(vel,vel,vel);
    ui->up_button->setAutoRepeat(true);
    ui->down_button->setAutoRepeat(true);
    ui->right_button->setAutoRepeat(true);
    ui->left_button->setAutoRepeat(true);

    gE545.loadFocusValuesFromFile();
    gE545.getFocusValues(focus);

    for(auto it : focus){
        std::cout<<it<<std::endl;
    }

    ui->deltaX_spinBox->setValue(focus[0]);
    ui->deltaY_spinBox->setValue(focus[1]);
    ui->stepSize_spinBox->setValue(stepSize);
    ui->vel_spinBox->setValue(vel);



    mMalkasten->scene->giveItAPointerToSettingsPage(this);
    spinBox_laserPosX = ui->spinBox_laserPosX;
    spinBox_laserPosY = ui->spinBox_laserPosY;
    spinBox_laserPosX->setEnabled(0);
    spinBox_laserPosY->setEnabled(0);
    spinBox_laserPosY->setMinimum(-5000);
    spinBox_laserPosY->setMaximum(5000);
    spinBox_laserPosX->setMinimum(-5000);
    spinBox_laserPosX->setMaximum(5000);
    spinBox_laserPosX->setValue(::gE545.itsLaserPosX);
    spinBox_laserPosY->setValue(::gE545.itsLaserPosY);

    std::cout<<"settingsPage::settingsPage(QWidget *parent) LEAVING"<<std::endl;
}

settingsPage::~settingsPage()
{
    delete ui;
}



void settingsPage::on_up_button_pressed()
{

    gE545.move(0,stepSize,0);

    gE545.getPositon(pos);
    ui->x_pos->setValue(pos[0]-tare[0]);
    ui->y_pos->setValue(pos[1]-tare[1]);

}

void settingsPage::on_down_button_pressed()
{

    gE545.move(0,-stepSize,0);

   gE545.getPositon(pos);

   ui->x_pos->setValue(pos[0]-tare[0]);
   ui->y_pos->setValue(pos[1]-tare[1]);

}

void settingsPage::on_left_button_pressed()
{

    gE545.move(-stepSize,0,0);

   gE545.getPositon(pos);
   ui->x_pos->setValue(pos[0]-tare[0]);
   ui->y_pos->setValue(pos[1]-tare[1]);


}

void settingsPage::on_right_button_pressed()
{

    gE545.move(stepSize,0,0);

   gE545.getPositon(pos);
   ui->x_pos->setValue(pos[0]-tare[0]);
   ui->y_pos->setValue(pos[1]-tare[1]);

}

void settingsPage::on_set_focus_values_clicked()
{

    double focus[3];
    focus[0]=ui->deltaX_spinBox->value();
    focus[1]=ui->deltaY_spinBox->value();
    focus[2]=0;

    gE545.setFocus_and_writeValuesToFile(focus);

}

void settingsPage::on_stepSize_spinBox_valueChanged(double arg1)
{
    stepSize= ui->stepSize_spinBox->value();
}


void settingsPage::on_vel_spinBox_valueChanged(double arg1)
{
    vel = ui->vel_spinBox->value();
}

void settingsPage::on_pushButton_clicked()
{
    gE545.getPositon(pos);

    for(int i = 0; i<3;i++){
        tare[i]=pos[i];
    }

    ui->x_pos->setValue(pos[0]-tare[0]);
    ui->y_pos->setValue(pos[1]-tare[1]);

}


void settingsPage::on_delayFactor_SpinBox_valueChanged(double arg1)
{
    ::macroDelayFactor=ui->delayFactor_SpinBox->value();
}

void settingsPage::on_pushButton_2_clicked()
{
    double pos[3];
    ::gE545.getPositon(pos);
    ui->x_pos->setValue(pos[0]);
    ui->y_pos->setValue(pos[1]);
}

void settingsPage::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        spinBox_laserPosX->setEnabled(1);
        spinBox_laserPosY->setEnabled(1);
        gE545.loadLaserPosValuesFromFile();
        mMalkasten->scene->laserSpot->setPos(gE545.itsLaserPosX,gE545.itsLaserPosY);
        mMalkasten->scene->addItem(mMalkasten->scene->laserSpot);
        mMalkasten->scene->laserSpot->setEnabled(1);
    }else
    {
        spinBox_laserPosX->setEnabled(0);
        spinBox_laserPosY->setEnabled(0);

        gE545.itsLaserPosX = mMalkasten->scene->laserSpot->x();
        gE545.itsLaserPosY = mMalkasten->scene->laserSpot->y();
        gE545.writeLaserPosValuesToFile();
        mMalkasten->scene->removeItem(mMalkasten->scene->laserSpot);
        spinBox_laserPosX->setValue(::gE545.itsLaserPosX);
        spinBox_laserPosY->setValue(::gE545.itsLaserPosY);
    }
}

void settingsPage::on_spinBox_laserPosX_editingFinished()
{
        mMalkasten->scene->laserSpot->setPos(spinBox_laserPosX->value(),spinBox_laserPosY->value());
        gE545.itsLaserPosX = mMalkasten->scene->laserSpot->x();
        gE545.itsLaserPosY = mMalkasten->scene->laserSpot->y();
        gE545.writeLaserPosValuesToFile();
}

void settingsPage::on_spinBox_laserPosY_editingFinished()
{
        mMalkasten->scene->laserSpot->setPos(spinBox_laserPosX->value(),spinBox_laserPosY->value());
        gE545.itsLaserPosX = mMalkasten->scene->laserSpot->x();
        gE545.itsLaserPosY = mMalkasten->scene->laserSpot->y();
        gE545.writeLaserPosValuesToFile();
}

void settingsPage::assignNewValuesToLaserPos()
{
    qDebug()<<"I GOT TRIGGERED";
    qDebug()<<mMalkasten->scene->laserSpot->pos();
    spinBox_laserPosX->setValue(mMalkasten->scene->laserSpot->x());
    spinBox_laserPosY->setValue(mMalkasten->scene->laserSpot->y());
    gE545.itsLaserPosX = mMalkasten->scene->laserSpot->x();
    gE545.itsLaserPosY = mMalkasten->scene->laserSpot->y();
    gE545.writeLaserPosValuesToFile();
}
