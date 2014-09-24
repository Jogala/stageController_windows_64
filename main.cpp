#include "mainwindow.h"
#include <QApplication>
#include "GlobalVariables.h"

int main(int argc, char *argv[])
{
    cout<<"main ENTERING "<<endl;
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    cout<<"main LEAVING"<<endl;
    return a.exec();
}
