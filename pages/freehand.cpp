#include "freehand.h"
#include "ui_freehand.h"

#include <QDebug>
#include "globalstagecontroller.h"

freeHand::freeHand(QWidget *parent,Malkasten * pToMainWindowsMalkasten) :
    QWidget(parent),mMalkasten(pToMainWindowsMalkasten),scene(pToMainWindowsMalkasten->scene), ui(new Ui::freeHand)
{
    ui->setupUi(this);
    qDebug()<<mMalkasten->height();

    mMalkasten->view->enableDrawFreeHand(ui->radioButton->isChecked());
    ui->spinBox_velocity->setMinimum(1);
    ui->spinBox_velocity->setMaximum(::gE545.itsVeloLimit);
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

void freeHand::on_pushButton_clear_clicked()
{
    mMalkasten->scene->removeAllNodes();
}

void freeHand::on_pushButton_cut_freeHand_press_clicked()
{
    mMalkasten->scene->writeCoordOfNodesToFile();
    ::gE545.createMacroFromCoordinatesAndCut("./cut_coords/coordFreeHand.txt","freeHand",ui->spinBox_velocity->value(),ui->doubleSpinBox_delayFactor->value());
}

void freeHand::on_pushButton_removeLastNode_clicked()
{
    scene->removeLastNode();
}
