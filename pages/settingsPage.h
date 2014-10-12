#ifndef settingsPage_H
#define settingsPage_H

#include "./globalstagecontroller.h"
#include "./GlobalVariables.h"
#include "screenShotWindow/malkasten.h"

namespace Ui {
class settingsPage;
}

class settingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit settingsPage( QWidget *parent = 0,Malkasten * pToMainWindowMalkasten = 0);
    ~settingsPage();

public slots:
    void assignNewValuesToLaswerPos();

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
    void on_pushButton_2_clicked();
    void on_radioButton_clicked(bool checked);
    void on_spinBox_laserPosX_editingFinished();
    void on_spinBox_laserPosY_editingFinished();

protected:

private:
    Ui::settingsPage *ui;

    //Set Focus
    double stepSize;
    double vel;
    double pos[3];
    double focus[3];
    double tare[3];

    Malkasten * mMalkasten;

    QSpinBox *spinBox_laserPosX;
    QSpinBox *spinBox_laserPosY;


};

#endif // settingsPage_H
