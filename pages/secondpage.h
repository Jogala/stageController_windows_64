#ifndef SECONDPAGE_H
#define SECONDPAGE_H

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


namespace Ui {
class secondPage;
}

class secondPage : public QWidget
{
    Q_OBJECT

public:
    explicit secondPage(QWidget *parent = 0);
    ~secondPage();

private slots:
    void on_open_shutter_clicked();

    void on_close_shutter_clicked();

    void on_pulse_button_clicked();

private:
    Ui::secondPage *ui;

};

#endif // SECONDPAGE_H
