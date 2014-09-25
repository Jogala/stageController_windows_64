#ifndef THIRDPAGE_H
#define THIRDPAGE_H

#include "./globalstagecontroller.h"
#include "./GlobalVariables.h"

namespace Ui {
class thirdPage;
}

class thirdPage : public QWidget
{
    Q_OBJECT

public:
    explicit thirdPage( QWidget *parent = 0);
    ~thirdPage();

private slots:

    void on_up_button_pressed();

    void on_down_button_pressed();

    void on_left_button_pressed();

    void on_right_button_pressed();

    void on_set_focus_values_clicked();

    void on_stepSize_spinBox_valueChanged(double arg1);

    void on_vel_spinBox_valueChanged(double arg1);

    void on_pushButton_clicked();


    void on_delayFactor_SpinBox_valueChanged(double arg1);

private:
    Ui::thirdPage *ui;

    //Set Focus
    double stepSize;
    double vel;
    double pos[3];
    double focus[3];
    double tare[3];

};

#endif // THIRDPAGE_H
