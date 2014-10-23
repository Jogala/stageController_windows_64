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

    void on_pushButton_clear_clicked();
    void on_pushButton_cut_freeHand_press_clicked();

    void on_pushButton_removeLastNode_clicked();


private:
    void loadFreeHandMacroDelayFactor();
    void writeDelayFactorToFile();

    Ui::freeHand *ui;
    Malkasten * mMalkasten;
    MeineSceneClass *scene;
};

#endif // FREEHAND_H
