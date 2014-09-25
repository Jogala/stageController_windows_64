#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    std::cout<<"MainWindow::MainWindow(QWidget *parent) ENTERING"<<std::endl;

    ui->setupUi(this);

    anzahlPages = 3;
    maxWidthFirstPage=1600;
    pagesGeom.resize(3,2);
    pagesGeom(0,0)=maxWidthFirstPage;
    pagesGeom(0,1)=550;
    pagesGeom(1,0)=410;
    pagesGeom(1,1)=500;
    pagesGeom(2,0)=830;
    pagesGeom(2,1)=450;


    QSize myIconSize(100,100);
    ui->mainToolBar->setIconSize(myIconSize);

    stackedWidget = new QStackedWidget(this);

    std::cout<<"allocate first Page on the heap START"<<std::endl;
    firstPageWidget= new firstPage(this);
    std::cout<<"allocate first Page on the heap DONE"<<std::endl;

    std::cout<<"allocate second Page on the heap START"<<std::endl;
    secondPageWidget= new secondPage(this);
    std::cout<<"allocate second Page on the heap DONE"<<std::endl;

    std::cout<<"allocate third Page on the heap START"<<std::endl;
    thirdPageWidget = new thirdPage(this);
    std::cout<<"allocate third Page on the heap DONE"<<std::endl;

    //////////////////////////////////////////////////////////
    //      Put firstPageWidget into a Scroll Area          //
    //////////////////////////////////////////////////////////
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(firstPageWidget);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //////////////////////////////////////////////////////////////
    //  assigns pages to switch between to a QstackedWidget     //
    //////////////////////////////////////////////////////////////
    stackedWidget->addWidget(scrollArea);
    stackedWidget->addWidget(secondPageWidget);
    stackedWidget->addWidget(thirdPageWidget);

    ////////////////////////////////////////////////////////////
    //      Show First Page and Adjust size of MainWindow     //
    ////////////////////////////////////////////////////////////
    this->setCentralWidget(stackedWidget);
    adjusMainWindowFor_firstPage();

    ui->mainToolBar->setMovable(false);

    std::cout<<"MainWindow::MainWindow(QWidget *parent) LEAVING"<<std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFigures_triggered()
{
    stackedWidget->setCurrentIndex(0);
    this->setCentralWidget(stackedWidget);
    gE545.moveTo(100,100,100);

    adjusMainWindowFor_firstPage();

}

void MainWindow::on_actionPuls_triggered()
{

    if(stackedWidget->currentIndex()==0){
        //Save current width of firstPage
        pagesGeom(0,0)=static_cast<QRect>(this->geometry()).width();
    }

    stackedWidget->setCurrentIndex(1);
    this->setCentralWidget(stackedWidget);

    adjusMainWindowFor_secondPage();
}


void MainWindow::on_actionSettings_triggered()
{

    if(stackedWidget->currentIndex()==0){
        //Save current width of firstPage
        pagesGeom(0,0)=static_cast<QRect>(this->geometry()).width();
    }

    stackedWidget->setCurrentIndex(2);
    this->setCentralWidget(stackedWidget);

    adjusMainWindowFor_thirdPage();
}

void MainWindow::adjusMainWindowFor_firstPage(){

    this->setFixedHeight(pagesGeom(0,1));
    this->setMaximumWidth(maxWidthFirstPage );
    this->resize(pagesGeom(0,0),pagesGeom(0,1));

}

void MainWindow::adjusMainWindowFor_secondPage(){

    this->setFixedSize(pagesGeom(1,0),pagesGeom(1,1));

}

void MainWindow::adjusMainWindowFor_thirdPage(){

    this->setFixedSize(pagesGeom(2,0),pagesGeom(2,1));
    this->resize(pagesGeom(2,0),pagesGeom(2,1));

}
