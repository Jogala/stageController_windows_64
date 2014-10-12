#include "fourthpage.h"
#include "ui_fourthpage.h"
#include <QLayout>


fourthPage::fourthPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fourthPage)
{
    ui->setupUi(this);
    myImDialogWin = new imageDialog(this);

    ui->pushButton_add_one_node->setEnabled(ui->checkBox_polygonzug->isChecked());
    ui->pushButton_remove_last_node->setEnabled(ui->checkBox_polygonzug->isChecked());
    ui->pushButton_cut_polygonzug->setEnabled(ui->checkBox_polygonzug->isChecked());
    ui->pushButton_done_set_position_of_laser->setEnabled(ui->checkBox_polygonzug->isChecked());
    ui->spinBox_vel_PolygonZug->setEnabled(ui->checkBox_polygonzug->isChecked());

    ui->spinBox_vel_PolygonZug->setMinimum(1);
    ui->spinBox_vel_PolygonZug->setMaximum(::gE545.veloLimit);

    ui->spinBox_laserX->setMinimum(-2000);
    ui->spinBox_laserX->setMaximum(2000);

    ui->spinBox_laserY->setMinimum(-2000);
    ui->spinBox_laserY->setMaximum(2000);

    ::gE545.loadLaserPosValuesFromFile();
    ui->spinBox_laserX->setValue(::gE545.itsLaserPosX);
    ui->spinBox_laserY->setValue(::gE545.itsLaserPosY);
    ui->spinBox_vel_PolygonZug->setValue(100);

    ui->spinBox_screenShot_x->setMaximum(5000);
    ui->spinBox_screenShot_y->setMaximum(5000);
    ui->spinBox_screenShot_w->setMaximum(5000);
    ui->spinBox_screenShot_h->setMaximum(5000);

    ui->spinBox_stepSize->setMinimum(1);
    ui->spinBox_stepSize->setMaximum(100);

    ui->spinBox_screenShot_x->setValue(myImDialogWin->widget->geomScreenShot.x());
    ui->spinBox_screenShot_y->setValue(myImDialogWin->widget->geomScreenShot.y());
    ui->spinBox_screenShot_w->setValue(myImDialogWin->widget->geomScreenShot.width());
    ui->spinBox_screenShot_h->setValue(myImDialogWin->widget->geomScreenShot.height());

}

fourthPage::~fourthPage()
{
    delete ui;
}

void fourthPage::on_pushButton_Refresh_Background_clicked()
{
    myImDialogWin->widget->refreshBackground();
}

void fourthPage::on_pushButton_open_window_clicked()
{
    myImDialogWin->setGeometry(3500,500,600,600);
    myImDialogWin->showMaximized();
}

void fourthPage::on_checkBox_polygonzug_stateChanged(int arg1)
{
    polygonzugModus=arg1;
    qDebug()<<arg1;

    if(polygonzugModus)
    {
        ui->pushButton_add_one_node->setEnabled(1);
        ui->spinBox_vel_PolygonZug->setEnabled(1);

        if(myImDialogWin->widget->nodeList.length())
        {
            ui->pushButton_remove_last_node->setEnabled(1);
            ui->pushButton_cut_polygonzug->setEnabled(1);
        }
    }
    else
    {
        ui->pushButton_add_one_node->setEnabled(0);
        ui->pushButton_remove_last_node->setEnabled(0);
        ui->spinBox_vel_PolygonZug->setEnabled(0);
    }
}

void fourthPage::on_pushButton_add_one_node_clicked()
{
    qDebug()<<"on_pushButton_add_one_node_clicked";

    myImDialogWin->widget->addNode();

    ui->pushButton_remove_last_node->setEnabled(1);
    ui->pushButton_cut_polygonzug->setEnabled(1);
}

void fourthPage::on_pushButton_remove_last_node_clicked()
{
    myImDialogWin->widget->removeNode();

    if(!myImDialogWin->widget->nodeList.length())
    {
        ui->pushButton_remove_last_node->setEnabled(0);
        ui->pushButton_cut_polygonzug->setEnabled(0);
    }
}

void fourthPage::on_pushButton_cut_polygonzug_clicked()
{
    myImDialogWin->widget->polygonZugSaveCoordinates();
    ::gE545.itsVelocityForMacro = ui->spinBox_vel_PolygonZug->value();
    ::gE545.createMacroFromCoordinates("./cut_coords/polygonZugCoord.txt");
}

void fourthPage::on_pushButton_start_set_position_of_laser_clicked()
{
    myImDialogWin->widget->addLaserSpotToScene();
    ui->pushButton_start_set_position_of_laser->setEnabled(0);
    ui->pushButton_done_set_position_of_laser->setEnabled(1);
}

void fourthPage::on_pushButton_done_set_position_of_laser_clicked()
{
    myImDialogWin->widget->writePosOfLaserSpotToFile_then_removeLaserSpotFromScene();
    ui->pushButton_start_set_position_of_laser->setEnabled(1);
    ui->pushButton_done_set_position_of_laser->setEnabled(0);

    ui->spinBox_laserX->setValue(::gE545.itsLaserPosX);
    ui->spinBox_laserY->setValue(::gE545.itsLaserPosY);

}



void fourthPage::on_pushButton_up_clicked()
{
    myImDialogWin->widget->geomScreenShot.setRect(
                                                    myImDialogWin->widget->geomScreenShot.x(),myImDialogWin->widget->geomScreenShot.y()-stepSizeScreenShot,
                                                    myImDialogWin->widget->geomScreenShot.width(),myImDialogWin->widget->geomScreenShot.height()
                                                  );

    ui->spinBox_screenShot_y->setValue(myImDialogWin->widget->geomScreenShot.y());

    myImDialogWin->widget->takeScreenShot();
    myImDialogWin->widget->refreshBackground();
}

void fourthPage::on_pushButton_right_clicked()
{
    myImDialogWin->widget->geomScreenShot.setRect(
                                                    myImDialogWin->widget->geomScreenShot.x()+stepSizeScreenShot,myImDialogWin->widget->geomScreenShot.y(),
                                                    myImDialogWin->widget->geomScreenShot.width(),myImDialogWin->widget->geomScreenShot.height()
                                                  );
    ui->spinBox_screenShot_y->setValue(myImDialogWin->widget->geomScreenShot.x());


    myImDialogWin->widget->takeScreenShot();
    myImDialogWin->widget->refreshBackground();
}

void fourthPage::on_pushButton_down_clicked()
{
    myImDialogWin->widget->geomScreenShot.setRect(
                                                    myImDialogWin->widget->geomScreenShot.x(),myImDialogWin->widget->geomScreenShot.y()-stepSizeScreenShot,
                                                    myImDialogWin->widget->geomScreenShot.width(),myImDialogWin->widget->geomScreenShot.height()
                                                  );

    ui->spinBox_screenShot_y->setValue(myImDialogWin->widget->geomScreenShot.y());


    myImDialogWin->widget->takeScreenShot();
    myImDialogWin->widget->refreshBackground();
}

void fourthPage::on_pushButton_left_clicked()
{
    myImDialogWin->widget->geomScreenShot.setRect(
                                                    myImDialogWin->widget->geomScreenShot.x()-stepSizeScreenShot,myImDialogWin->widget->geomScreenShot.y(),
                                                    myImDialogWin->widget->geomScreenShot.width(),myImDialogWin->widget->geomScreenShot.height()
                                                  );
    ui->spinBox_screenShot_y->setValue(myImDialogWin->widget->geomScreenShot.x());


    myImDialogWin->widget->takeScreenShot();
    myImDialogWin->widget->refreshBackground();
}

void fourthPage::on_spinBox_stepSize_valueChanged(int arg1)
{
    stepSizeScreenShot=arg1;
}

void fourthPage::on_spinBox_screenShot_x_valueChanged(int arg1)
{
    myImDialogWin->widget->geomScreenShot.setX(arg1);

    myImDialogWin->widget->takeScreenShot();
    myImDialogWin->widget->refreshBackground();
}

void fourthPage::on_spinBox_screenShot_y_valueChanged(int arg1)
{
    myImDialogWin->widget->geomScreenShot.setY(arg1);

    myImDialogWin->widget->takeScreenShot();
    myImDialogWin->widget->refreshBackground();
}

void fourthPage::on_spinBox_screenShot_w_valueChanged(int arg1)
{
    myImDialogWin->widget->geomScreenShot.setWidth(arg1);

    myImDialogWin->widget->takeScreenShot();
    myImDialogWin->widget->refreshBackground();
}

void fourthPage::on_spinBox_screenShot_h_valueChanged(int arg1)
{
    myImDialogWin->widget->geomScreenShot.setHeight(arg1);

    myImDialogWin->widget->takeScreenShot();
    myImDialogWin->widget->refreshBackground();
}

