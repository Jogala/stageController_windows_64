#ifndef pulsePage_H
#define pulsePage_H

#include "./GlobalVariables.h"
#include "./globalstagecontroller.h"

#include <QWidget>
#include <QWidget>
#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QAbstractTextDocumentLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QAbstractSpinBox>
#include <QTextEdit>
#include "QDoubleSpinBox"
#include <QScrollArea>
#include <QShortcut>
#include <QKeySequence>
#include <QStackedWidget>
#include <QComboBox>
#include <QThread>

#include "screenShotWindow/malkasten.h"
#include "screenShotWindow/meinesceneclass.h"

namespace Ui {
class pulsePage;
}

class pulsePage : public QWidget
{
    Q_OBJECT

public:
    explicit pulsePage(QWidget *parent = 0, Malkasten * pToMainWindowsMalkasten=0);
    ~pulsePage();

private slots:
    void on_open_shutter_clicked();

    void on_close_shutter_clicked();

    void on_pulse_button_clicked();

    void on_pushButton_refreshBackground_clicked();


    void on_open_shutter__blueDot_clicked();

    void on_close_shutter___blueDot_clicked();

    void on_radioButton_clicked(bool checked);

    void on_pulse_button___blueDot_clicked();


private:
    Ui::pulsePage *ui;
    Malkasten *mMalkasten;
    MeineSceneClass * scene;

};

#endif // pulsePage_H
