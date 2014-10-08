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
    QRect rec  = myImDialogWin->rect();
    myImDialogWin->setGeometry(2000,500,rec.width(),rec.height());
    myImDialogWin->show();
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
