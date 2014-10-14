#ifndef EINSTELLUNGEN_H
#define EINSTELLUNGEN_H

#include <QWidget>
#include "screenShotWindow/malkasten.h"
#include "./globalstagecontroller.h"
#include "./GlobalVariables.h"
#include "screenShotWindow/meinesceneclass.h"

namespace Ui {
class Einstellungen;
}

class Einstellungen : public QWidget
{
    Q_OBJECT

public:
    explicit Einstellungen(QWidget *parent = 0, Malkasten *pToMainWindowsMalkasten =0 );
    ~Einstellungen();



private slots:

    void saveScreenShotGeometry();
    void assignNewValuesToLaserPos();
    void assignNewValuesToSpinBoxLineLength();
    void loadUFactors();
    void saveUFactors();
    void loadScreenShotGeometry();

    //////////////////////////////////////////////////

    void on_pushButton_refreshBackground_clicked();

    void on_checkBox_laserSpot_clicked(bool checked);
    void on_spinBox_laserPosX_editingFinished();
    void on_spinBox_laserPosY_editingFinished();

    void on_spinBox_screenShot_x_editingFinished();
    void on_spinBox_screenShot_y_editingFinished();
    void on_spinBox_screenShot_w_editingFinished();
    void on_spinBox_screenShot_h_editingFinished();

    void on_checkBox__showScaleBar_clicked(bool checked);
    void on_doubleSpinBox_meterstab_x1_valueChanged(double arg1);
    void on_doubleSpinBox_meterstab_x2_valueChanged(double arg1);
    void on_doubleSpinBox_length_real_valueChanged();
    void on_pushButton_setConversionFac_clicked();

    void on_up_button_pressed();
    void on_down_button_pressed();
    void on_left_button_pressed();
    void on_right_button_pressed();
    void on_tare_button_clicked();
    void on_pushButton_reset_clicked();
    void on_set_focus_values_clicked();
    void on_vel_spinBox_valueChanged(double arg1);
    void on_stepSize_spinBox_valueChanged(double arg1);

    void on_delayFactor_SpinBox_valueChanged(double arg1);



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
