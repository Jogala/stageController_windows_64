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

    loadFreeHandMacroDelayFactor();

    //Set Shortcut
    QShortcut *refreshBackground = new QShortcut(QKeySequence("R"), this);
    QObject::connect(refreshBackground, SIGNAL(activated()), mMalkasten, SLOT(refreshBackground()));

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

    writeDelayFactorToFile();
    if(scene->nodeFreeHandList.length())
    {
    mMalkasten->scene->writeCoordOfNodesToFile();
    ::gE545.createMacroFromCoordinatesAndCut("./cut_coords/coordFreeHand.txt","freeHand",ui->spinBox_velocity->value(),ui->doubleSpinBox_delayFactor->value());
    }
}

void freeHand::on_pushButton_removeLastNode_clicked()
{
    scene->removeLastNode();
}

void freeHand::loadFreeHandMacroDelayFactor()
{
    std::cout<<"void freeHand::loadFreeHandMacroDelayFactor()ENTERING"<<std::endl;
    double delay;
    std::fstream f;
    f.open("./Stored_Values/delayFactor_FreeHandMacro.txt");
    f>>delay;
    f.close();

        std::cout<<delay<<std::endl;

        ui->doubleSpinBox_delayFactor->setValue(delay);

    std::cout<<"void freeHand::loadFreeHandMacroDelayFactor()LEAVING"<<std::endl;
}

void freeHand::writeDelayFactorToFile()
{
    std::cout<<"void freeHand::writeDelayFactorToFile()ENTERING"<<std::endl;

    //save delay factor in stored files
    std::fstream f;
    f.open("./Stored_Values/delayFactor_FreeHandMacro.txt", std::fstream::out | std::fstream::trunc);
    if(f.is_open())
    {
        f<<ui->doubleSpinBox_delayFactor->value()<<std::endl;
        f.close();
    }

    std::cout<<"void freeHand::writeDelayFactorToFile()LEAVING"<<std::endl;

}



