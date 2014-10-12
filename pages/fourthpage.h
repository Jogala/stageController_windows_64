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

    void on_pushButton_Refresh_Background_clicked();

    void on_pushButton_open_window_clicked();


    void on_checkBox_polygonzug_stateChanged(int arg1);

    void on_pushButton_add_one_node_clicked();

    void on_pushButton_remove_last_node_clicked();

    void on_pushButton_cut_polygonzug_clicked();

    void on_pushButton_start_set_position_of_laser_clicked();

    void on_pushButton_done_set_position_of_laser_clicked();



    void on_pushButton_up_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_left_clicked();

    void on_spinBox_stepSize_valueChanged(int arg1);

    void on_spinBox_screenShot_x_valueChanged(int arg1);

    void on_spinBox_screenShot_y_valueChanged(int arg1);

    void on_spinBox_screenShot_w_valueChanged(int arg1);

    void on_spinBox_screenShot_h_valueChanged(int arg1);

private:
    Ui::fourthPage *ui;
    imageDialog * myImDialogWin;
    bool polygonzugModus;
    int stepSizeScreenShot = 1;


};

#endif // FOURTHPAGE_H
