#ifndef FIRSTPAGE_H
#define FIRSTPAGE_H

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

#include "Figures/figures.h"
#include "Figures/line.h"
#include "Figures/polygon.h"
#include "Figures/rectangle.h"
#include "Figures/spiral.h"
#include "Figures/stripes.h"

#include "screenShotWindow/meinesceneclass.h"
#include "screenShotWindow/malkasten.h"

namespace Ui {
class firstPage;
}

class firstPage : public QWidget
{
    Q_OBJECT

public:

    explicit firstPage(QWidget *parent = 0,  Malkasten *pToMainWindowsMalkasten =0 );
    ~firstPage();

private slots:

    void on_checkBox_figuresLaserDot_clicked(bool checked);
    void on_pushButton_refreshBackground_clicked();

    void moveToFigureLaserSpot();

    void readOutValuesFromRecTable();
    void readOutValuesFromStripesTable();
    bool readOutValuesFromSpiralTable();
    void readOutValuesFromPolygonTable();


    void on_line_cut_clicked();
    void on_rec_cut_clicked();
    void on_stripes_cut_clicked();
    void on_poly_cut_clicked();
    void on_spiral_cut_clicked();

    void setFocus_lineTable();
    void setFocus_recTable();
    void setFocus_polyTable();
    void setFocus_spiralTable();
    void setFocus_stripesTable();

    void on_pushButton_spiral_cut_at_dot_clicked();
    void on_pushButton_poly_cut_at_dot_clicked();
    void on_pushButton_stripes_cut_at_dot_clicked();
    void on_pushButton_rec_cut_at_dot_clicked();
    void on_pushButton_line_cut_at_dot_clicked();




private:
    Ui::firstPage *ui;

    Malkasten * mMalkasten;
    MeineSceneClass * scene;

    QTableWidget * recTable;
    QTableWidget * polyTable;
    QTableWidget * spiralTable;
    QTableWidget * lineTable;
    QTableWidget * stripesTable;

    //figures
    figures::rectangle  mRectangle;
    figures::polygon    mPoly;
    figures::spiral     mSpiral;
    figures::line       mLine;
    figures::stripes    mStripes;

    int cWidth;
    double veloMax;
    double maxA;
    void setUp_RecTable();
    void setUp_LineTable();
    void setUp_PolyTable();
    void setUp_SpiralTable();
    void setUp_StripesTable();
    void setShortcuts();
};

#endif // FIRSTPAGE_H
