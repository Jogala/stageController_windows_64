#ifndef EINSTELLUNGEN_H
#define EINSTELLUNGEN_H

#include <QWidget>
#include "./globalstagecontroller.h"
#include "./GlobalVariables.h"
#include "screenShotWindow/malkasten.h"
#include "screenShotWindow/meinesceneclass.h"

namespace Ui {
class Einstellungen;
}

class Einstellungen : public QWidget
{
    Q_OBJECT

public:
    explicit Einstellungen(QWidget *parent = 0, Malkasten* pToMainWindowsMalkasten=0);
    ~Einstellungen();

public slots:
    void assignNewValuesToLaserPos();
    void assignNewValuesToSpinBoxLineLength();

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

    void on_pushButton_refreshBackground_clicked();

    void on_doubleSpinBox_meterstab_x1_valueChanged(double arg1);

    void on_doubleSpinBox_meterstab_x2_valueChanged(double arg1);

    void on_doubleSpinBox_length_real_valueChanged(double arg1);

    void on_pushButton_3_clicked();

    void loadUFactors();
    void saveUFactors();

    void on_spinBox_screenShot_x_editingFinished();
    void on_spinBox_screenShot_y_editingFinished();
    void on_spinBox_screenShot_w_editingFinished();
    void on_spinBox_screenShot_h_editingFinished();
    void loadScreenShotGeometry();
    void saveScreenShotGeometry();


private:
    Ui::Einstellungen *ui;

    //Set Focus
    double stepSize;
    double vel;
    double pos[3];
    double focus[3];
    double tare[3];

    Malkasten * mMalkasten;
    MeineSceneClass * scene;

    QSpinBox *spinBox_laserPosX;
    QSpinBox *spinBox_laserPosY;
};

#endif // EINSTELLUNGEN_H






