#include "imagedialog.h"
#include "ui_imagedialog.h"
#include <QLayout>

imageDialog::imageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imageDialog)
{
    ui->setupUi(this);
    widget = new GraphWidget(this);

    QVBoxLayout *mLay = new QVBoxLayout(this);
    mLay->addWidget(widget);

}

imageDialog::~imageDialog()
{
    delete ui;
}


