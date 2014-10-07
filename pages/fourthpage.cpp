#include "fourthpage.h"
#include "ui_fourthpage.h"
#include <QLayout>


fourthPage::fourthPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fourthPage)
{
    ui->setupUi(this);
    myImDialogWin = new imageDialog(this);

}

fourthPage::~fourthPage()
{
    delete ui;
}



void fourthPage::on_pushButton_clicked()
{
    QRect rec  = myImDialogWin->rect();
    myImDialogWin->setGeometry(2000,500,rec.width(),rec.height());
    myImDialogWin->show();
}

void fourthPage::on_pushButton_2_clicked()
{
    myImDialogWin->widget->refreshBackground();
}
