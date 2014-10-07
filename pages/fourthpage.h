#ifndef FOURTHPAGE_H
#define FOURTHPAGE_H

#include "./screenShot/imagedialog.h"
#include "./screenShot/edge.h"
#include "./screenShot/graphwidget.h"
#include "./screenShot/node.h"
#include "Header.h"
#include <QWidget>

namespace Ui {
class fourthPage;
}

class fourthPage : public QWidget
{
    Q_OBJECT

public:

    explicit fourthPage(QWidget *parent = 0);

    ~fourthPage();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::fourthPage *ui;
    imageDialog * myImDialogWin;

};

#endif // FOURTHPAGE_H
