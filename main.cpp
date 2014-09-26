#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <string>
#include "GlobalVariables.h"

int main(int argc, char *argv[])
{
    std::cout<<"main ENTERING "<<std::endl;
    QApplication a(argc, argv);

//    std::cout<<"include relative path to Qt_dlls folder START"<<std::endl;
//    QString pathToExe = QCoreApplication::applicationFilePath();
//    QString nameOfExe = QFileInfo( QCoreApplication::applicationFilePath() ).fileName();
//    std::string strPathToQtDlls = pathToExe.toStdString();
//    strPathToQtDlls = strPathToQtDlls.erase(pathToExe.length()-nameOfExe.length(),pathToExe.length());
//    strPathToQtDlls = strPathToQtDlls+"Qt_dlls/";
//    std::cout<<strPathToQtDlls<<std::endl;
//    QCoreApplication::addLibraryPath(QString::fromUtf8(strPathToQtDlls.c_str()));
//    std::cout<<"include relative path to Qt_dlls folder DONE"<<std::endl;


    MainWindow w;
    w.show();

    std::cout<<"main LEAVING"<<std::endl;
    std::cout<<"#################################################################"<<std::endl;
    std::cout<<"#               SETUP DONE, WAITING FOR USER ACTION             #"<<std::endl;
    std::cout<<"#################################################################"<<std::endl;
    return a.exec();
}
