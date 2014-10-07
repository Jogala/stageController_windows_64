#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QDialog>
#include "./screenShot/graphwidget.h"

namespace Ui {
class imageDialog;
}

class imageDialog : public QDialog
{
    Q_OBJECT

public:
    GraphWidget *widget;
    explicit imageDialog(QWidget *parent = 0);
    ~imageDialog();

private slots:


private:
    Ui::imageDialog *ui;

};

#endif // IMAGEDIALOG_H
