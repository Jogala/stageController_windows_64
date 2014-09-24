#-------------------------------------------------
#
# Project created by QtCreator 2014-09-18T19:38:17
#
#-------------------------------------------------

QT       += core gui

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
    pages/secondpage.cpp \
    pages/thirdpage.cpp

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
    pages/secondpage.h \
    pages/thirdpage.h

FORMS    += mainwindow.ui \
    pages/firstpage.ui \
    pages/secondpage.ui \
    pages/thirdpage.ui

INCLUDEPATH += $$PWD/Eigen_Linear_Algebra_Library\

INCLUDEPATH += $$PWD/

RESOURCES += \
    Resources.qrc


