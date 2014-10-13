#-------------------------------------------------
#
# Project created by QtCreator 2014-09-18T19:38:17
#
#-------------------------------------------------

QT       += core gui quick

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stageController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stageController.cpp \
    usefulFunctions.cpp \
    GlobalVariables.cpp \
    Figures/line.cpp \
    Figures/polygon.cpp \
    Figures/rectangle.cpp \
    Figures/spiral.cpp \
    Figures/surfaceRec.cpp \
    pages/firstpage.cpp \
    globalstagecontroller.cpp \
    pages/freehand.cpp \
    screenShotWindow/edge.cpp \
    screenShotWindow/malkasten.cpp \
    screenShotWindow/meinesceneclass.cpp \
    screenShotWindow/meineviewclass.cpp \
    screenShotWindow/node.cpp \
    screenShotWindow/laserSpot.cpp \
    pages/settingsPage.cpp \
    pages/pulsePage.cpp \
    screenShotWindow/meterstab.cpp \
    pages/settingspage.cpp


HEADERS  += mainwindow.h \
    stageController.h \
    usefulFunctions.h \
    Header.h \
    GlobalVariables.h \
    Figures/figures.h \
    Figures/line.h \
    Figures/polygon.h \
    Figures/rectangle.h \
    Figures/spiral.h \
    pages/firstpage.h \
    pages/pulsePage.h \
    pages/settingsPage.h \
    globalstagecontroller.h \
    pages/freehand.h \
    screenShotWindow/edge.h \
    screenShotWindow/malkasten.h \
    screenShotWindow/meinesceneclass.h \
    screenShotWindow/meineviewclass.h \
    screenShotWindow/node.h \
    pages/settingsPage.h \
    screenShotWindow/laserSpot.h \
    screenShotWindow/meterstab.h \
    pages/settingspage.h


FORMS    += mainwindow.ui \
    pages/firstpage.ui \
    pages/fourthpage.ui \
    pages/freehand.ui \
    pages/pulsePage.ui \
    pages/settingspage.ui


INCLUDEPATH += $$PWD/Eigen_Linear_Algebra_Library\

INCLUDEPATH += $$PWD/

RESOURCES += \
    Resources.qrc

LIBS += $$PWD/PI_stuff/PI_GCS2_DLL_x64.lib\



