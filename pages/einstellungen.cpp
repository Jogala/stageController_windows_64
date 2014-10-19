#include "einstellungen.h"
#include "ui_einstellungen.h"

Einstellungen::Einstellungen(QWidget *parent, Malkasten * pToMalkasten) :
    QWidget(parent), mMalkasten(pToMalkasten),scene(pToMalkasten->scene),
    ui(new Ui::Einstellungen)
{

    std::cout<<std::endl;
    std::cout<<"###########################################################"<<std::endl;
    std::cout<<"###########################################################"<<std::endl;
    std::cout<<"settingsPage::settingsPage(QWidget *parent) ENTERING"<<std::endl;

    ui->setupUi(this);

    scene->giveItAPointerToSettingsPage(this);
    spinBox_laserPosX = ui->spinBox_laserPosX;
    spinBox_laserPosY = ui->spinBox_laserPosY;
    spinBox_laserPosX->setValue(::gE545.itsLaserPosX);
    spinBox_laserPosY->setValue(::gE545.itsLaserPosY);

    for(auto item : tare){
        item = 0;
    }

    ui->delayFactor_SpinBox->setValue(::macroDelayFactor);
    gE545.getPositon(pos);
    ui->x_pos->setValue(pos[0]);
    ui->y_pos->setValue(pos[1]);
    gE545.setVelocity(1000,1000,1000);

    ui->up_button->setAutoRepeat(true);
    ui->down_button->setAutoRepeat(true);
    ui->right_button->setAutoRepeat(true);
    ui->left_button->setAutoRepeat(true);



    loadFocusValuesAndAssignThem();
    loadConversionFactorParametersAndAssignThem();
    loadScreenShotGeometry();


    std::cout<<"settingsPage::settingsPage(QWidget *parent) LEAVING"<<std::endl;
}

Einstellungen::~Einstellungen()
{
    delete ui;
}

void Einstellungen::on_pushButton_refreshBackground_clicked()
{
    mMalkasten->refreshBackground();
}


void Einstellungen::on_checkBox_laserSpot_clicked(bool checked)
{

    qDebug()<<"on_checkBox_laserSpot_clicked"<<checked;

    if(checked)
    {
        spinBox_laserPosX->setEnabled(1);
        spinBox_laserPosY->setEnabled(1);

        if(!scene->laserSpot->isVisible()){
        scene->laserSpot->show();
        }
        scene->laserSpot->setEnabled(1);


    }else
    {
        spinBox_laserPosX->setEnabled(0);
        spinBox_laserPosY->setEnabled(0);

        gE545.itsLaserPosX = scene->laserSpot->x();
        gE545.itsLaserPosY = scene->laserSpot->y();
        gE545.writeLaserPosValuesToFile();
        scene->laserSpot->hide();
        spinBox_laserPosX->setValue(::gE545.itsLaserPosX);
        spinBox_laserPosY->setValue(::gE545.itsLaserPosY);
    }
}

void Einstellungen::on_spinBox_screenShot_x_editingFinished()
{
    mMalkasten->recScreenShot.setX(ui->spinBox_screenShot_x->value());
        saveScreenShotGeometry();
        mMalkasten->refreshBackground();
}

void Einstellungen::on_spinBox_screenShot_y_editingFinished()
{
    mMalkasten->recScreenShot.setY(ui->spinBox_screenShot_y->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();
}

void Einstellungen::on_spinBox_screenShot_w_editingFinished()
{
    mMalkasten->recScreenShot.setWidth(ui->spinBox_screenShot_w->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();
}

void Einstellungen::on_spinBox_screenShot_h_editingFinished()
{
    mMalkasten->recScreenShot.setHeight(ui->spinBox_screenShot_h->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();
}

void Einstellungen::saveScreenShotGeometry()
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

void Einstellungen::on_doubleSpinBox_meterstab_x1_valueChanged(double arg1)
{
    qDebug()<<"x1";
    qDebug()<<scene->meterstab->line();

    scene->meterstab->setLine(
                                arg1,
                                scene->meterstab->line().y1(),
                                scene->meterstab->line().x2(),
                                scene->meterstab->line().y2()
                              );

    double lengthPix =  ui->doubleSpinBox_meterstab_length->value();
    double lengthReal = ui->doubleSpinBox_length_real->value();
    ui->doubleSpinBox_meterstab_length->setValue(scene->meterstab->line().length());
    ui->doubleSpinBox_uFactor->setValue(lengthReal/lengthPix);
}

void Einstellungen::on_doubleSpinBox_meterstab_x2_valueChanged(double arg1)
{
    qDebug()<<"x2";
    scene->meterstab->setLine(
                                scene->meterstab->line().x1(),
                                scene->meterstab->line().y1(),
                                arg1,
                                scene->meterstab->line().y2()
                              );

    double lengthPix =  ui->doubleSpinBox_meterstab_length->value();
    double lengthReal = ui->doubleSpinBox_length_real->value();
    ui->doubleSpinBox_meterstab_length->setValue(scene->meterstab->line().length());
    ui->doubleSpinBox_uFactor->setValue(lengthReal/lengthPix);
}

void Einstellungen::on_doubleSpinBox_length_real_valueChanged()
{
    double lengthPix =  ui->doubleSpinBox_meterstab_length->value();
    double lengthReal = ui->doubleSpinBox_length_real->value();
    ui->doubleSpinBox_meterstab_length->setValue(scene->meterstab->line().length());
    ui->doubleSpinBox_uFactor->setValue(lengthReal/lengthPix);
}

void Einstellungen::on_pushButton_setConversionFac_clicked()
{
    double lengthPix =  ui->doubleSpinBox_meterstab_length->value();
    double lengthReal = ui->doubleSpinBox_length_real->value();
    scene->uFactorFromSceneToStage = lengthReal/lengthPix;
    saveConversionFactorParameters();
}

void Einstellungen::loadConversionFactorParametersAndAssignThem()
{

    std::string storedValuesPath = "./Stored_Values/uFactors.txt";

    double originMeterstabX;
    double originMeterstabY;
    double meterstabX1;
    double meterstabX2;
    double realLength;
    double uFac;

    std::fstream f;
    f.open(storedValuesPath);

    if (f.is_open()) {

        f>>originMeterstabX;
        f>>originMeterstabY;
        f>>meterstabX1;
        f>>meterstabX2;
        f>>realLength;
        f>>uFac;
    }
    f.close();


    scene->meterstab->moveBy(originMeterstabX,originMeterstabY);

    ui->doubleSpinBox_meterstab_x1->setValue(meterstabX1);
    ui->doubleSpinBox_meterstab_x2->setValue(meterstabX2);
    scene->meterstab->setLine(
                                meterstabX1,
                                0,
                                meterstabX2,
                                0
                              );

    ui->doubleSpinBox_length_real->setValue(realLength);

    scene->uFactorFromSceneToStage = uFac;
    ui->doubleSpinBox_uFactor->setValue(uFac);

}

void Einstellungen::saveConversionFactorParameters()
{
    std::string storedValuesPath = "./Stored_Values/uFactors.txt";
    std::fstream f;
    f.open(storedValuesPath);

    if (f.is_open())
    {

        std::cout<<"STORE UFACTOR VALUES"<<std::endl;
        std::cout<<"#########################################################################"<<std::endl;
        std::cout<<"#########################################################################"<<std::endl;
        std::cout<<"#########################################################################"<<std::endl;

        std::cout<<scene->meterstab->pos().x()<<std::endl;
        std::cout<<scene->meterstab->pos().y()<<std::endl;
        std::cout<<scene->meterstab->line().x1()<<std::endl;
        std::cout<<scene->meterstab->line().x2()<<std::endl;
        std::cout<<ui->doubleSpinBox_length_real->value()<<std::endl;
        std::cout<<ui->doubleSpinBox_uFactor->value()<<std::endl;


        f<<scene->meterstab->pos().x()<<std::endl;
        f<<scene->meterstab->pos().y()<<std::endl;
        f<<scene->meterstab->line().x1()<<std::endl;
        f<<scene->meterstab->line().x2()<<std::endl;
        f<<ui->doubleSpinBox_length_real->value()<<std::endl;
        f<<ui->doubleSpinBox_uFactor->value()<<std::endl;


        std::cout<<"#########################################################################"<<std::endl;
        std::cout<<"#########################################################################"<<std::endl;
        std::cout<<"#########################################################################"<<std::endl;


    }
    f.close();
}



void Einstellungen::on_up_button_pressed()
{
    gE545.move(0,stepSize,0);

    gE545.getPositon(pos);
    ui->x_pos->setValue(pos[0]-tare[0]);
    ui->y_pos->setValue(pos[1]-tare[1]);
}

void Einstellungen::on_down_button_pressed()
{
    gE545.move(0,-stepSize,0);

   gE545.getPositon(pos);

   ui->x_pos->setValue(pos[0]-tare[0]);
   ui->y_pos->setValue(pos[1]-tare[1]);
}

void Einstellungen::on_left_button_pressed()
{
    gE545.move(-stepSize,0,0);

   gE545.getPositon(pos);
   ui->x_pos->setValue(pos[0]-tare[0]);
   ui->y_pos->setValue(pos[1]-tare[1]);

}

void Einstellungen::on_right_button_pressed()
{
    gE545.move(stepSize,0,0);

   gE545.getPositon(pos);
   ui->x_pos->setValue(pos[0]-tare[0]);
   ui->y_pos->setValue(pos[1]-tare[1]);

}


void Einstellungen::on_tare_button_clicked()
{
    gE545.getPositon(pos);

    for(int i = 0; i<3;i++){
        tare[i]=pos[i];
    }

    ui->x_pos->setValue(pos[0]-tare[0]);
    ui->y_pos->setValue(pos[1]-tare[1]);
}

void Einstellungen::on_delayFactor_SpinBox_valueChanged(double arg1)
{
    ::macroDelayFactor=ui->delayFactor_SpinBox->value();
}


void Einstellungen::on_set_focus_values_clicked()
{
    double focus[3];
    focus[0]=ui->x_pos->value();
    focus[1]=ui->y_pos->value();
    focus[2]=0;

    gE545.setFocusValues_and_writeValuesToFile(focus);
}

void Einstellungen::on_vel_spinBox_valueChanged(double arg1)
{
    vel = ui->vel_spinBox->value();
}

void Einstellungen::on_stepSize_spinBox_valueChanged(double arg1)
{
    stepSize= ui->stepSize_spinBox->value();
}

void Einstellungen::on_spinBox_laserPosX_editingFinished()
{
    scene->laserSpot->setPos(spinBox_laserPosX->value(),spinBox_laserPosY->value());
    gE545.itsLaserPosX = scene->laserSpot->x();
    gE545.itsLaserPosY = scene->laserSpot->y();
    gE545.writeLaserPosValuesToFile();
}

void Einstellungen::on_spinBox_laserPosY_editingFinished()
{
    scene->laserSpot->setPos(spinBox_laserPosX->value(),spinBox_laserPosY->value());
    gE545.itsLaserPosX = scene->laserSpot->x();
    gE545.itsLaserPosY = scene->laserSpot->y();
    gE545.writeLaserPosValuesToFile();
}

void Einstellungen::assignNewValuesToLaserPos()
{
    qDebug()<<"I GOT TRIGGERED";
    qDebug()<<scene->laserSpot->pos();
    spinBox_laserPosX->setValue(scene->laserSpot->x());
    spinBox_laserPosY->setValue(scene->laserSpot->y());
    gE545.itsLaserPosX = scene->laserSpot->x();
    gE545.itsLaserPosY = scene->laserSpot->y();
    gE545.writeLaserPosValuesToFile();
}

void Einstellungen::assignNewValuesToSpinBoxLineLength()
{
    ui->doubleSpinBox_meterstab_length->setValue(scene->meterstab->line().length());
}


void Einstellungen::loadScreenShotGeometry()
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

void Einstellungen::loadFocusValuesAndAssignThem()
{

    gE545.loadFocusValuesFromFile();

    ui->x_pos->setValue(::gE545.getFocusValue(0));
    ui->y_pos->setValue(::gE545.getFocusValue(1));
    stepSize = ui->stepSize_spinBox->value();
}

void Einstellungen::on_pushButton_reset_clicked()
{
        double pos[3];
        ::gE545.getPositon(pos);
        ui->x_pos->setValue(pos[0]);
        ui->y_pos->setValue(pos[1]);
}

void Einstellungen::on_checkBox__showScaleBar_clicked(bool checked)
{
    if(checked)
    {
        scene->meterstab->show();
    }
    else
    {
        scene->meterstab->hide();
    }
}


