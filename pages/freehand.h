#ifndef FREEHAND_H
#define FREEHAND_H

#include <QWidget>
#include "screenShotWindow/malkasten.h"

namespace Ui {
class freeHand;
}

class freeHand : public QWidget
{
    Q_OBJECT

public:
    explicit freeHand(QWidget *parent = 0,Malkasten * pToMinWindowsMalkasten = 0 );
    ~freeHand();

private slots:
    void on_radioButton_clicked(bool checked);

    void on_pushButton_refreshBackground_clicked();

    void on_spinBox_screenShot_x_editingFinished();
    void on_spinBox_screenShot_y_editingFinished();
    void on_spinBox_screenShot_w_editingFinished();
    void on_spinBox_screenShot_h_editingFinished();

    void loadScreenShotGeometry();
    void saveScreenShotGeometry();

    void loadUFactors();
    void saveUFactors();

    void on_pushButton_clear_clicked();
    void on_pushButton_cut_freeHand_press_clicked();
    void on_doubleSpinBox_uFactor_editingFinished();

private:
    Ui::freeHand *ui;
    Malkasten * mMalkasten;
};

#endif // FREEHAND_H
