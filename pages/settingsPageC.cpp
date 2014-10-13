#include "settingsPage.h"
#include "ui_settingsPage.h"
#include <QTime>

settingsPage::settingsPage(QWidget *parent, Malkasten * pToMainWindowsMalkasten) :
    QWidget(parent), mMalkasten(pToMainWindowsMalkasten), scene(pToMainWindowsMalkasten->scene), ui(new Ui::settingsPage)
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

    scene->giveItAPointerToSettingsPage(this);
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

    ui->doubleSpinBox_meterstab_length->setReadOnly(1);

    loadUFactors();
    loadScreenShotGeometry();


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

void settingsPage::on_spinBox_laserPosX_editingFinished()
{
        scene->laserSpot->setPos(spinBox_laserPosX->value(),spinBox_laserPosY->value());
        gE545.itsLaserPosX = scene->laserSpot->x();
        gE545.itsLaserPosY = scene->laserSpot->y();
        gE545.writeLaserPosValuesToFile();
}

void settingsPage::on_spinBox_laserPosY_editingFinished()
{
        scene->laserSpot->setPos(spinBox_laserPosX->value(),spinBox_laserPosY->value());
        gE545.itsLaserPosX = scene->laserSpot->x();
        gE545.itsLaserPosY = scene->laserSpot->y();
        gE545.writeLaserPosValuesToFile();
}

void settingsPage::assignNewValuesToLaserPos()
{
    qDebug()<<"I GOT TRIGGERED";
    qDebug()<<scene->laserSpot->pos();
    spinBox_laserPosX->setValue(scene->laserSpot->x());
    spinBox_laserPosY->setValue(scene->laserSpot->y());
    gE545.itsLaserPosX = scene->laserSpot->x();
    gE545.itsLaserPosY = scene->laserSpot->y();
    gE545.writeLaserPosValuesToFile();
}

void settingsPage::assignNewValuesToSpinBoxLineLength()
{
    ui->doubleSpinBox_meterstab_length->setValue(scene->meterstab->line().length());
}

void settingsPage::on_pushButton_refreshBackground_clicked()
{
    mMalkasten->refreshBackground();
}

void settingsPage::on_doubleSpinBox_meterstab_x1_valueChanged(double arg1)
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

void settingsPage::on_doubleSpinBox_meterstab_x2_valueChanged(double arg1)
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


void settingsPage::on_doubleSpinBox_length_real_valueChanged(double arg1)
{
    double lengthPix =  ui->doubleSpinBox_meterstab_length->value();
    double lengthReal = ui->doubleSpinBox_length_real->value();
    ui->doubleSpinBox_meterstab_length->setValue(scene->meterstab->line().length());
    ui->doubleSpinBox_uFactor->setValue(lengthReal/lengthPix);
}

void settingsPage::on_pushButton_3_clicked()
{
    double lengthPix =  ui->doubleSpinBox_meterstab_length->value();
    double lengthReal = ui->doubleSpinBox_length_real->value();
    scene->uFaktorFromSceneToStage = lengthReal/lengthPix;
    saveUFactors();

}

void settingsPage::loadUFactors()
{

    std::string storedValuesPath = "./Stored_Values/uFactors.txt";

    double uFac;
    std::fstream f;
    f.open(storedValuesPath);

    if (f.is_open()) {

        f>>uFac;

    }
    f.close();

    scene->uFaktorFromSceneToStage = uFac;
    ui->doubleSpinBox_uFactor->setValue(uFac);

}
void settingsPage::saveUFactors()
{
    std::string storedValuesPath = "./Stored_Values/uFactors.txt";
    std::fstream f;
    f.open(storedValuesPath);

    if (f.is_open()) {

        f<<ui->doubleSpinBox_uFactor;
    }
    f.close();
}

void settingsPage::on_spinBox_screenShot_x_editingFinished()
{
    mMalkasten->recScreenShot.setX(ui->spinBox_screenShot_x->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();

}
void settingsPage::on_spinBox_screenShot_y_editingFinished()
{
    mMalkasten->recScreenShot.setY(ui->spinBox_screenShot_y->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();

}
void settingsPage::on_spinBox_screenShot_w_editingFinished()
{
    mMalkasten->recScreenShot.setWidth(ui->spinBox_screenShot_w->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();

}
void settingsPage::on_spinBox_screenShot_h_editingFinished()
{
    mMalkasten->recScreenShot.setHeight(ui->spinBox_screenShot_h->value());
    saveScreenShotGeometry();
    mMalkasten->refreshBackground();

}

void settingsPage::loadScreenShotGeometry()
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
void settingsPage::saveScreenShotGeometry()
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

void settingsPage::on_radioButton_2_clicked(bool checked)
{

        ui->radioButton_2->setChecked(0);

}
