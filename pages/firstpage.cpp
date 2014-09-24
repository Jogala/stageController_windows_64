#include "firstpage.h"
#include "ui_firstpage.h"

firstPage::firstPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::firstPage)
{
    cout<<"Entering constructor firstPage"<<endl;

    ui->setupUi(this);

    cWidth = 10;
    veloMax=9900;
    maxA=195;

    setUp_LineTable();
    setUp_RecTable();
    setUp_PolyTable();
    setUp_SpiralTable();

    QShortcut *ctrl_l = new QShortcut(QKeySequence("CTRL+L"), this);
    QObject::connect(ctrl_l, SIGNAL(activated()), this, SLOT(setFocus_lineTable()));

    QShortcut *shortCut_ctrl_r = new QShortcut(QKeySequence("CTRL+R"), this);
    QObject::connect(shortCut_ctrl_r, SIGNAL(activated()), this, SLOT(setFocus_recTable()));

    QShortcut *shortCut_ctrl_p = new QShortcut(QKeySequence("CTRL+P"), this);
    QObject::connect(shortCut_ctrl_p, SIGNAL(activated()), this, SLOT(setFocus_polyTable()));

    QShortcut *shortCut_ctrl_s = new QShortcut(QKeySequence("CTRL+S"), this);
    QObject::connect(shortCut_ctrl_s, SIGNAL(activated()), this, SLOT(setFocus_spiralTable()));

    for(int i = 0; i<lineTable->rowCount()-1 ; i++)
    {
        this->setTabOrder(static_cast<QSpinBox*>(lineTable->cellWidget(i,1)),static_cast<QSpinBox*>(lineTable->cellWidget(i+1,1)));
    }
    this->setTabOrder(static_cast<QSpinBox*>(lineTable->cellWidget(4,1)),ui->line_cut);

    for(int i = 0; i<recTable->rowCount()-1 ; i++)
    {
        this->setTabOrder(static_cast<QSpinBox*>(recTable->cellWidget(i,1)),static_cast<QSpinBox*>(recTable->cellWidget(i+1,1)));
    }
    this->setTabOrder(static_cast<QSpinBox*>(recTable->cellWidget(5,1)),ui->rec_cut);

    for(int i = 0; i<polyTable->rowCount()-1 ; i++)
    {
        this->setTabOrder(static_cast<QSpinBox*>(polyTable->cellWidget(i,1)),static_cast<QSpinBox*>(polyTable->cellWidget(i+1,1)));
    }
    this->setTabOrder(static_cast<QSpinBox*>(polyTable->cellWidget(5,1)),ui->poly_cut);


    for(int i = 0; i<spiralTable->rowCount()-1 ; i++)
    {
        this->setTabOrder(static_cast<QSpinBox*>(spiralTable->cellWidget(i,1)),static_cast<QSpinBox*>(spiralTable->cellWidget(i+1,1)));
    }
    this->setTabOrder(static_cast<QSpinBox*>(spiralTable->cellWidget(7,1)),ui->spiral_cut);

    gE545.printMemberVariables();
    cout<<"Leaving constructor firstPage"<<endl;


}

firstPage::~firstPage()
{
    delete ui;
}

void firstPage::setUp_LineTable(){

    lineTable=ui->lineTable;
    lineTable->verticalHeader()->setVisible(false);
    lineTable->horizontalHeader()->setVisible(false);
    lineTable->setShowGrid(false);
    //column 2 is only used as a spacer
    lineTable->setColumnWidth(2,cWidth);
    lineTable->setTabKeyNavigation(false);

    //////////////////////////////////////////
    //          Format 1. Column            //
    //////////////////////////////////////////

    for(int i = 0; i<lineTable->rowCount() ; i++)
    {
        lineTable->item(i,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }

    //make 1. Column unaccesible
    for(int i = 0;i<lineTable->rowCount();i++){

        lineTable->item(i,0)->setFlags(lineTable->item(i,0)->flags() ^ Qt::ItemIsEditable);
        lineTable->item(i,0)->setFlags(lineTable->item(i,0)->flags() ^ Qt::ItemIsSelectable);
        lineTable->item(i,0)->setFlags(lineTable->item(i,0)->flags() ^ Qt::ItemIsUserCheckable);
    }

    // http://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/MAC/GREEK.TXT
    lineTable->item(1,0)->setText(QString(QChar(0x03C6))+" =");
    lineTable->item(2,0)->setText(QString(QChar(0x0398))+" =");


    //////////////////////////////////////////////////////////
    //      Put DoubleSpinBoxes in 2.Column of Table        //
    //////////////////////////////////////////////////////////
    for( int i = 0; i < lineTable->rowCount(); i++ )
    {

        if(i==3){
            QSpinBox *spinBox = new QSpinBox();
            spinBox->setValue(0);
            lineTable->setCellWidget( i, 1, spinBox );
        }else
        {

            QDoubleSpinBox *spinBox = new QDoubleSpinBox();
            spinBox->setValue(0);
            lineTable->setCellWidget( i, 1, spinBox );
        }
    }

    //Format SpinBoxes Manually

    static_cast<QSpinBox*>(lineTable->cellWidget(0,1))->setMinimum(0);
    static_cast<QSpinBox*>(lineTable->cellWidget(0,1))->setMaximum(maxA/2);

    static_cast<QSpinBox*>(lineTable->cellWidget(1,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(lineTable->cellWidget(1,1))->setMaximum(1000);

    static_cast<QSpinBox*>(lineTable->cellWidget(2,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(lineTable->cellWidget(2,1))->setMaximum(1000);

    static_cast<QSpinBox*>(lineTable->cellWidget(3,1))->setMinimum(1);
    static_cast<QSpinBox*>(lineTable->cellWidget(3,1))->setMaximum(1000);

    static_cast<QSpinBox*>(lineTable->cellWidget(4,1))->setMinimum(0);
    static_cast<QSpinBox*>(lineTable->cellWidget(4,1))->setMaximum(veloMax);

    ////////////////////////////////////////////////////////////////////////////////////////
    //      Load stored values from text file  and assign them in 3. and 2. Column        //
    ////////////////////////////////////////////////////////////////////////////////////////
    QFile lineFile(QString::fromStdString(mLine.getStoredValuesPath()));
    lineFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream inLine(&lineFile);
    for( int i = 0; i < lineTable->rowCount(); i++ )
    {
        if(i==3){
            QLabel *label = new QLabel();
            int x = inLine.readLine().toInt();
            label->setNum(x);
            cout<<x<<endl;
            label->setAlignment(Qt::AlignVCenter);
            lineTable->setCellWidget( i, 3, label );
            static_cast<QSpinBox*>(lineTable->cellWidget(i,1))->setValue(x);
        }else
        {
            QLabel *label = new QLabel();
            double x = inLine.readLine().toDouble();

            if((i==1)||(i==2)){
                x=(x/(2*pi))*360;
            }

            label->setNum(x);
            cout<<x<<endl;
            label->setAlignment(Qt::AlignVCenter);
            lineTable->setCellWidget( i, 3, label );
            static_cast<QDoubleSpinBox*>(lineTable->cellWidget(i,1))->setValue(x);
        }
    }
    lineFile.close();

}

void firstPage::setUp_RecTable(){

    recTable=ui->recTable;
    recTable->verticalHeader()->setVisible(false);
    recTable->horizontalHeader()->setVisible(false);
    recTable->setShowGrid(false);

    //Format 1. Column
    for(int i = 0; i<recTable->rowCount() ; i++)
    {
        recTable->item(i,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }

    //////////////////////////////////////////////////////////
    //      Put DoubleSpinBoxes in 2.Column of Table        //
    //////////////////////////////////////////////////////////
    for( int i = 0; i < recTable->rowCount(); i++ )
    {

        QDoubleSpinBox *spinBox = new QDoubleSpinBox();
        spinBox->setValue(0);
        recTable->setCellWidget( i, 1, spinBox );

    }

    //Format SpinBoxes Manually

    static_cast<QSpinBox*>(recTable->cellWidget(0,1))->setMinimum(0);
    static_cast<QSpinBox*>(recTable->cellWidget(0,1))->setMaximum(maxA);

    static_cast<QSpinBox*>(recTable->cellWidget(1,1))->setMinimum(0);
    static_cast<QSpinBox*>(recTable->cellWidget(1,1))->setMaximum(maxA);

    static_cast<QSpinBox*>(recTable->cellWidget(2,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(recTable->cellWidget(2,1))->setMaximum(1000);

    static_cast<QSpinBox*>(recTable->cellWidget(3,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(recTable->cellWidget(3,1))->setMaximum(1000);

    static_cast<QSpinBox*>(recTable->cellWidget(4,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(recTable->cellWidget(4,1))->setMaximum(1000);

    static_cast<QSpinBox*>(recTable->cellWidget(5,1))->setMinimum(0);
    static_cast<QSpinBox*>(recTable->cellWidget(5,1))->setMaximum(veloMax);

    ////////////////////////////////////////////////////////////////////////
    //      Load stored values and assign them in 3. and 2. Column        //
    ////////////////////////////////////////////////////////////////////////
    cout<<mRectangle.getStoredValuesPath()<<endl;
    QFile recFile(QString::fromStdString(mRectangle.getStoredValuesPath()));
    recFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream inRec(&recFile);
    for( int i = 0; i < recTable->rowCount(); i++ )
    {
        QLabel *label = new QLabel();
        double x = inRec.readLine().toDouble();

        if((i==2)||(i==3)||(i==4)){
            x=(x/(2*pi))*360;
        }


        label->setNum(x);
        cout<<x<<endl;
        label->setAlignment(Qt::AlignVCenter);
        recTable->setCellWidget( i, 3, label );
        static_cast<QDoubleSpinBox*>(recTable->cellWidget(i,1))->setValue(x);
    }
    recFile.close();


    //make 1. Column unaccesible
    for(int i = 0;i<recTable->rowCount();i++){

        recTable->item(i,0)->setFlags(recTable->item(i,0)->flags() ^ Qt::ItemIsEditable);
        recTable->item(i,0)->setFlags(recTable->item(i,0)->flags() ^ Qt::ItemIsSelectable);
        recTable->item(i,0)->setFlags(recTable->item(i,0)->flags() ^ Qt::ItemIsUserCheckable);
        //recTable->item(i,0)->setFlags(recTable->item(i,0)->flags() ^ Qt::ItemIsEnabled);
    }


    recTable->setColumnWidth(2,cWidth);
    recTable->setTabKeyNavigation(false);


}

void firstPage::setUp_PolyTable(){

    polyTable=ui->polyTable;
    polyTable->verticalHeader()->setVisible(false);
    polyTable->horizontalHeader()->setVisible(false);
    polyTable->setShowGrid(false);

    //Format 1. Column
    for(int i = 0; i<polyTable->rowCount() ; i++)
    {
        polyTable->item(i,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }


    //////////////////////////////////////////////////////////
    //      Put DoubleSpinBoxes in 2.Column of Table        //
    //////////////////////////////////////////////////////////
    for( int i = 0; i < polyTable->rowCount(); i++ )
    {
        QDoubleSpinBox *spinBox = new QDoubleSpinBox();
        spinBox->setValue(0);
        polyTable->setCellWidget( i, 1, spinBox );
    }

    //Format SpinBoxes Manually

    static_cast<QSpinBox*>(polyTable->cellWidget(0,1))->setMinimum(0);
    static_cast<QSpinBox*>(polyTable->cellWidget(0,1))->setMaximum(maxA/2);

    static_cast<QSpinBox*>(polyTable->cellWidget(1,1))->setMinimum(0);
    static_cast<QSpinBox*>(polyTable->cellWidget(1,1))->setMaximum(1000);

    static_cast<QSpinBox*>(polyTable->cellWidget(2,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(polyTable->cellWidget(2,1))->setMaximum(1000);

    static_cast<QSpinBox*>(polyTable->cellWidget(3,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(polyTable->cellWidget(3,1))->setMaximum(1000);

    static_cast<QSpinBox*>(polyTable->cellWidget(4,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(polyTable->cellWidget(4,1))->setMaximum(1000);

    static_cast<QSpinBox*>(polyTable->cellWidget(5,1))->setMinimum(0);
    static_cast<QSpinBox*>(polyTable->cellWidget(5,1))->setMaximum(veloMax);

    ////////////////////////////////////////////////////////////////////////
    //      Load stored values and assign them in 3. and 2. Column        //
    ////////////////////////////////////////////////////////////////////////
    cout<<mPoly.getStoredValuesPath()<<endl;
    QFile polyFile(QString::fromStdString(mPoly.getStoredValuesPath()));
    polyFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream inPoly(&polyFile);
    for( int i = 0; i < polyTable->rowCount(); i++ )
    {
        QLabel *label = new QLabel();

        double x = inPoly.readLine().toDouble();
        label->setNum(x);
        cout<<x<<endl;
        label->setAlignment(Qt::AlignVCenter);
        polyTable->setCellWidget( i, 3, label );
        static_cast<QDoubleSpinBox*>(polyTable->cellWidget(i,1))->setValue(x);
    }
    polyFile.close();


    //make 1. Column unaccesible
    for(int i = 0;i<polyTable->rowCount();i++){

        polyTable->item(i,0)->setFlags(polyTable->item(i,0)->flags() ^ Qt::ItemIsEditable);
        polyTable->item(i,0)->setFlags(polyTable->item(i,0)->flags() ^ Qt::ItemIsSelectable);
        polyTable->item(i,0)->setFlags(polyTable->item(i,0)->flags() ^ Qt::ItemIsUserCheckable);
        //polyTable->item(i,0)->setFlags(polyTable->item(i,0)->flags() ^ Qt::ItemIsEnabled);
    }


    polyTable->setColumnWidth(2,cWidth);
    polyTable->setTabKeyNavigation(false);

}

void firstPage::setUp_SpiralTable(){


    ////////////////////////////////////////////
    //          Set up spiral Table           //
    ////////////////////////////////////////////

    spiralTable=ui->spiralTable;
    spiralTable->verticalHeader()->setVisible(false);
    spiralTable->horizontalHeader()->setVisible(false);
    spiralTable->setShowGrid(false);

    //Format 1. Column
    for(int i = 0; i<spiralTable->rowCount() ; i++)
    {
        spiralTable->item(i,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }


    //////////////////////////////////////////////////////////
    //      Put DoubleSpinBoxes in 2.Column of Table        //
    //////////////////////////////////////////////////////////

    for( int i = 0; i < spiralTable->rowCount(); i++ )
    {
        QDoubleSpinBox *spinBox = new QDoubleSpinBox();
        spinBox->setValue(0);
        spiralTable->setCellWidget( i, 1, spinBox );
    }

    static_cast<QSpinBox*>(spiralTable->cellWidget(0,1))->setMinimum(0);
    static_cast<QSpinBox*>(spiralTable->cellWidget(0,1))->setMaximum(maxA/2);

    static_cast<QSpinBox*>(spiralTable->cellWidget(1,1))->setMinimum(0);
    static_cast<QSpinBox*>(spiralTable->cellWidget(1,1))->setMaximum(maxA/2);

    static_cast<QSpinBox*>(spiralTable->cellWidget(2,1))->setMinimum(0);
    static_cast<QSpinBox*>(spiralTable->cellWidget(2,1))->setMaximum(10000);

    static_cast<QSpinBox*>(spiralTable->cellWidget(3,1))->setMinimum(0);
    static_cast<QSpinBox*>(spiralTable->cellWidget(3,1))->setMaximum(10000);

    static_cast<QSpinBox*>(spiralTable->cellWidget(4,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(spiralTable->cellWidget(4,1))->setMaximum(1000);

    static_cast<QSpinBox*>(spiralTable->cellWidget(5,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(spiralTable->cellWidget(5,1))->setMaximum(1000);

    static_cast<QSpinBox*>(spiralTable->cellWidget(6,1))->setMinimum(-1000);
    static_cast<QSpinBox*>(spiralTable->cellWidget(6,1))->setMaximum(1000);

    static_cast<QSpinBox*>(spiralTable->cellWidget(7,1))->setMinimum(0);
    static_cast<QSpinBox*>(spiralTable->cellWidget(7,1))->setMaximum(veloMax);


    ////////////////////////////////////////////////////////////////////////
    //      Load stored values and assign them in 3. and 2. Column        //
    ////////////////////////////////////////////////////////////////////////

    cout<<mSpiral.getStoredValuesPath()<<endl;
    QFile spiralFile(QString::fromStdString(mSpiral.getStoredValuesPath()));
    spiralFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream inspiral(&spiralFile);
    for( int i = 0; i < spiralTable->rowCount(); i++ )
    {
        QLabel *label = new QLabel();

        double x = inspiral.readLine().toDouble();

        if((i==4)||(i==5)||(i==6)){
            x=(x/(2*pi))*360;
        }

        label->setNum(x);
        cout<<x<<endl;
        label->setAlignment(Qt::AlignVCenter);
        spiralTable->setCellWidget( i, 3, label );
        static_cast<QDoubleSpinBox*>(spiralTable->cellWidget(i,1))->setValue(x);
    }
    spiralFile.close();


    //make 1. Column unaccesible
    for(int i = 0;i<spiralTable->rowCount();i++){

        spiralTable->item(i,0)->setFlags(spiralTable->item(i,0)->flags() ^ Qt::ItemIsEditable);
        spiralTable->item(i,0)->setFlags(spiralTable->item(i,0)->flags() ^ Qt::ItemIsSelectable);
        spiralTable->item(i,0)->setFlags(spiralTable->item(i,0)->flags() ^ Qt::ItemIsUserCheckable);
        //spiralTable->item(i,0)->setFlags(spiralTable->item(i,0)->flags() ^ Qt::ItemIsEnabled);
    }


    spiralTable->setColumnWidth(2,cWidth);
    spiralTable->setTabKeyNavigation(false);

}



void firstPage::on_line_cut_clicked()
{

    mLine.delayFactor=::macroDelayFactor;

    double x;
    //Assing values from DoubelSpinBoxes to Line
    for(int i=0;i<5;i++)
    {

        x=static_cast<QDoubleSpinBox*>(lineTable->cellWidget(i,1))->value();
        static_cast<QLabel*>(lineTable->cellWidget(i,3))->setText(QString::number(x));

        //convert it to rad
        if((i==1)||(i==2))
        {
            x=(x/360)*2*pi;
        }

        mLine.setValue(i,x);

    }

    //Write the Values also to the txt file, s.t, when the Program is closed and started again, those values get loaded
    mLine.writeValuesToTextFile();

    mLine.printMemberVariables();
    mLine.cutAbsLim3D();

    cout<<"lin cut done"<<endl;
}

void firstPage::on_rec_cut_clicked()
{

    mRectangle.delayFactor=::macroDelayFactor;


    double x;
    //Assing values from DoubelSpinBoxes to Rectangle
    for(int i=0;i<6;i++)
    {

        x=static_cast<QDoubleSpinBox*>(recTable->cellWidget(i,1))->value();
        static_cast<QLabel*>(recTable->cellWidget(i,3))->setText(QString::number(x));

        //convert it to rad
        if((i==2)||(i==3)||(i==4))
        {
            x=(x/(360))*2*pi;
        }

        mRectangle.setValue(i,x);

    }

    //Write the Values also to the txt file, s.t, when the Program is closed and started again, those values get loaded
    mRectangle.writeValuesToTextFile();


    mRectangle.printMemberVariables();
    mRectangle.cutAbs3D();
}

void firstPage::on_poly_cut_clicked()
{

    mPoly.delayFactor=::macroDelayFactor;


    double x;
    //Assing values from DoubelSpinBoxes to Poly
    for(int i=0;i<6;i++)
    {

        x=static_cast<QDoubleSpinBox*>(polyTable->cellWidget(i,1))->value();
        static_cast<QLabel*>(polyTable->cellWidget(i,3))->setText(QString::number(x));

        //convert it to rad
        if((i==2)||(i==3)||(i==4))
        {
            x=(x/(360))*2*pi;
        }

        mPoly.setValue(i,x);

    }

    //Write the Values also to the txt file, s.t, when the Program is closed and started again, those values get loaded
    mPoly.writeValuesToTextFile();

    mPoly.printMemberVariables();
    mPoly.cutAbsViaMacro3D();
}

void firstPage::on_spiral_cut_clicked()
{

     mSpiral.delayFactor=::macroDelayFactor;

    double x;
    //Assing values from DoubelSpinBoxes to Spiral
    for(int i=0;i<8;i++)
    {

        x=static_cast<QDoubleSpinBox*>(spiralTable->cellWidget(i,1))->value();
        static_cast<QLabel*>(spiralTable->cellWidget(i,3))->setText(QString::number(x));

        //convert it to rad
        if((i==4)||(i==5)||(i==6))
        {
            x=(x/(360))*2*pi;
        }

        mSpiral.setValue(i,x);

    }

    //Write the Values also to the txt file, s.t, when the Program is closed and started again, those values get loaded
    mSpiral.writeValuesToTextFile();

    mSpiral.printMemberVariables();
    mSpiral.cutAbsMacroSpiral3D();
}


void firstPage::setFocus_lineTable(){

    static_cast<QSpinBox*>(lineTable->cellWidget(0,1))->setFocus();
    static_cast<QSpinBox*>(lineTable->cellWidget(0,1))->selectAll();
}

void firstPage::setFocus_recTable(){

    static_cast<QSpinBox*>(recTable->cellWidget(0,1))->setFocus();
    static_cast<QSpinBox*>(recTable->cellWidget(0,1))->selectAll();
}

void firstPage::setFocus_polyTable(){

    static_cast<QSpinBox*>(polyTable->cellWidget(0,1))->setFocus();
    static_cast<QSpinBox*>(polyTable->cellWidget(0,1))->selectAll();
}

void firstPage::setFocus_spiralTable(){

    static_cast<QSpinBox*>(spiralTable->cellWidget(0,1))->setFocus();
    static_cast<QSpinBox*>(spiralTable->cellWidget(0,1))->selectAll();
}
