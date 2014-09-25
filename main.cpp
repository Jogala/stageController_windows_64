#include "mainwindow.h"
#include <QApplication>
#include "GlobalVariables.h"

int main(int argc, char *argv[])
{
    std::cout<<"main ENTERING "<<endl;
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    std::cout<<"main LEAVING"<<std::endl;
    std::cout<<"#################################################################"<<std::endl;
    std::cout<<"#               SETUP DONE, WAITING FOR USER ACTION             #"<<std::endl;
    std::cout<<"#################################################################"<<std::endl;
    return a.exec();
}
