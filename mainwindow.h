#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Header.h"

#include "pages/firstpage.h"
#include "pages/secondpage.h"
#include "pages/thirdpage.h"
#include "pages/freehand.h"

#include "screenShotWindow/malkasten.h"
#include "screenShotWindow/meineviewclass.h"
#include "screenShotWindow/meinesceneclass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    void adjusMainWindowFor_firstPage();
    void adjusMainWindowFor_secondPage();
    void adjusMainWindowFor_thirdPage();
    void adjusMainWindowFor_fourthPage();

    void killMe()
    {
    #ifdef Q_OS_WIN
        enum { ExitCode = 0 };
        ::TerminateProcess(::GetCurrentProcess(), ExitCode);
    #else
        qint64 pid = QCoreApplication::applicationPid();
        QProcess::startDetached("kill -9 " + QString::number(pid));
    #endif // Q_OS_WIN
    }

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionFigures_triggered();
    void on_actionSettings_triggered();
    void on_actionPuls_triggered();
    void on_actionFreehand_triggered();


private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    QRect recMenuBar;

    firstPage *firstPageWidget;
    secondPage *secondPageWidget;
    thirdPage *thirdPageWidget;
    freeHand * freeHandWidget;

    Eigen::MatrixXi pagesGeom;
    int maxWidthFirstPage;

    //ScreenShotWindow
    Malkasten * mMalkasten;
};

#endif // MAINWINDOW_H
