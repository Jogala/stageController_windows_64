#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    std::cout<<"MainWindow::MainWindow(QWidget *parent) ENTERING"<<std::endl;

    ui->setupUi(this);

    this->setWindowTitle("Laser Ablation");

    bool youForgotToTurnInitOn = 0;

    if(youForgotToTurnInitOn){
      QMessageBox::information(this,"initialize","YOU FORGOT TO CALL THE FUNCTION INIT !!!! turn youForgotToTurnInitOn to 0 and compile it again");

    }
        else{        

        QMessageBox m;
        m.setStandardButtons(0);
        m.setText("trying to connect via RS232 with E545");
        m.show();

        if(::gE545.initialize()==0)
        {
             m.close();
             QMessageBox::information(this,"initialize","Could not establish connection to E545 via RS232");
        }

    }

    maxWidthFirstPage=1600;
    pagesGeom.resize(4,2);
    pagesGeom(0,0)=maxWidthFirstPage;
    pagesGeom(0,1)=550;
    pagesGeom(1,0)=600;
    pagesGeom(1,1)=650;
    pagesGeom(2,0)=860;
    pagesGeom(2,1)=900;
    pagesGeom(3,0)=900;
    pagesGeom(3,1)=800;


    QSize myIconSize(100,100);
    ui->mainToolBar->setIconSize(myIconSize);

    //Screen Shot window
    mMalkasten = new Malkasten(this);
    mMalkasten->show();

    stackedWidget = new QStackedWidget(this);

    std::cout<<"allocate first Page on the heap START"<<std::endl;
    firstPageWidget= new firstPage(this);
    std::cout<<"allocate first Page on the heap DONE"<<std::endl;

    std::cout<<"allocate second Page on the heap START"<<std::endl;
    pulsePageWidget= new pulsePage(this,mMalkasten);
    std::cout<<"allocate second Page on the heap DONE"<<std::endl;

    std::cout<<"allocate third Page on the heap START"<<std::endl;
    settingsPageWidget = new Einstellungen(this,mMalkasten);
    std::cout<<"allocate third Page on the heap DONE"<<std::endl;

    std::cout<<"allocate fourth Page on the heap START"<<std::endl;
    freeHandWidget = new freeHand(this,mMalkasten);
    std::cout<<"allocate fourth Page on the heap DONE"<<std::endl;

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
    stackedWidget->addWidget(pulsePageWidget);
    stackedWidget->addWidget(settingsPageWidget);
    stackedWidget->addWidget(freeHandWidget);

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

    adjusMainWindowFor_pulsePage();
}

void MainWindow::on_actionSettings_triggered()
{

    if(stackedWidget->currentIndex()==0){
        //Save current width of firstPage
        pagesGeom(0,0)=static_cast<QRect>(this->geometry()).width();
    }

    stackedWidget->setCurrentIndex(2);
    this->setCentralWidget(stackedWidget);

    adjusMainWindowFor_settingsPage();
}

void MainWindow::on_actionFreehand_triggered()
{
    if(stackedWidget->currentIndex()==0){
        //Save current width of firstPage
        pagesGeom(0,0)=static_cast<QRect>(this->geometry()).width();
    }

    stackedWidget->setCurrentIndex(3);
    this->setCentralWidget(stackedWidget);

    adjusMainWindowFor_fourthPage();
}


void MainWindow::adjusMainWindowFor_firstPage(){

    this->setFixedHeight(pagesGeom(0,1));
    this->setMaximumWidth(maxWidthFirstPage );
    this->resize(pagesGeom(0,0),pagesGeom(0,1));

}

void MainWindow::adjusMainWindowFor_pulsePage(){

    this->setFixedSize(pagesGeom(1,0),pagesGeom(1,1));

}

void MainWindow::adjusMainWindowFor_settingsPage(){

    this->setFixedSize(pagesGeom(2,0),pagesGeom(2,1));
    this->resize(pagesGeom(2,0),pagesGeom(2,1));

}

void MainWindow::adjusMainWindowFor_fourthPage(){

    //this->setFixedSize(pagesGeom(3,0),pagesGeom(3,1));
    this->setMaximumWidth(3000);
    this->setMaximumHeight(3000);
    this->resize(pagesGeom(3,0),pagesGeom(3,1));

}


