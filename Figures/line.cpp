#include "line.h"
#include <QDir>
#include <QDebug>
void    figures::line::loadValuesFromTextFile(){

    fstream f;

    f.open(storedValuesPath);

    if (f.is_open()) {

        for(auto item : itsValues){
            f>>item;
        }
    }
    f.close();

}
void    figures::line::writeValuesToTextFile(){

   fstream f;
   f.open(storedValuesPath);

   cout<<"writing values to "<<storedValuesPath<<endl;
   for(auto item : itsValues)
   {
       cout<<item<<endl;
       f<<item<<endl;
   }

   f.close();
}

void    figures::line::setValue(int i, double value){

    itsValues[i]=value;

}
double  figures::line::getValue(int i){

    return itsValues[i];
}

void    figures::line::printMemberVariables(){

    cout<<"PRINT MEMBER VARIABLES"<<endl;
    int i = 0;
    for(auto item : itsValues){
        cout<<i++<<" "<<item<<endl;
        cout<<"C++11"<<endl;
    }

}


void figures::line::cutAbs3D(){

    cout<<endl;
    cout<<endl;
    cout<<"ENTER void figures::line::cutAbs3D()"<<endl;


    double l = itsValues[0];
    double phi = itsValues[1];
    double theta= itsValues[2];
    double repetitions= itsValues[3];
    double velocity = itsValues[4];

    if (repetitions < 1){

        cout << endl;
        cout << "ERROR:" << endl;
        cout << "repetitions has to be >= 1" << endl;

    }
    else{

        ::gE545.setVelocity(velocity, velocity, velocity);

        double vec[3];
        auto storagePos = vector<vector<double>>(repetitions, vector<double>(3));

        double pos[3];
        ::gE545.getPositon(pos);

        cout<<"########################################################################"<<endl;
        cout<<"in figures::line::cutAbs3D() get focus values"<<endl;
        double focus[3];
        ::gE545.getFocusValues(focus);
        cout<<"in figures::line::cutAbs3D() get focus values DONE"<<endl;
        cout<<"#########################################################################"<<endl;

        vec[0] = l*cos(phi)*sin(theta);
        vec[1] = l*sin(phi)*sin(theta);
        vec[2] = l*cos(theta);

        //////////////////////////////////////////////////////////////////////////
        //		Generating the sequence of coordinates that will be visited		//
        //////////////////////////////////////////////////////////////////////////


        for (int i = 0; i < repetitions; i++)
        {
            if (i % 2 == 0){
                storagePos[i][0] = pos[0] + vec[0];
                storagePos[i][1] = pos[1] + vec[1];
                storagePos[i][2] = pos[2] + vec[2];
            }

            if (i % 2 == 1){
                storagePos[i][0] = pos[0];
                storagePos[i][1] = pos[1];
                storagePos[i][2] = pos[2];
            }
        }
        //////////////////////////////////////////////////////
        //		Write sequence to file for controle			//
        //////////////////////////////////////////////////////

        use.writeCoordToFile("line3DAbs.txt", storagePos, repetitions);


        //////////////////////////////////////////
        //		Actual cutting procedure 		//
        //////////////////////////////////////////

        ::gE545.openShutter();
        for (int i = 0; i < repetitions; i++){
            cout << " cut number " << i+1 << endl;
            ::gE545.moveTo(storagePos[i][0], storagePos[i][1], storagePos[i][2]);

        }
        ::gE545.closeShutter();
        ::gE545.setVelocity(9000, 9000, 9000);
        ::gE545.moveTo(pos[0] +focus[0] + vec[0] / 2, pos[1] + focus[1]+ vec[1] / 2, pos[2] + focus[2]+ vec[2] / 2);
    }//else

    cout<<"LEAVE void figures::line::cutAbs3D()"<<endl;


}
void figures::line::cutAbsLim3D(){

    cout<<endl;
    cout<<endl;
    cout<<"void figures::line::cutAbsLim3D() ENTER"<<endl;

    double l = itsValues[0];
    double phi = itsValues[1];
    double theta= itsValues[2];
    double repetitions= itsValues[3];
    double velocity = itsValues[4];

    if (repetitions < 1){

        cout << endl;
        cout << "ERROR:" << endl;
        cout << "repetitions has to be >= 1" << endl;

    }
    else{

        ::gE545.setVelocity(velocity, velocity, velocity);

        double vec[3];
        double pos[3];
        auto storagePos = vector<vector<double>>(repetitions, vector<double>(3));

        ::gE545.getPositon(pos);

        vec[0] = l*cos(phi)*sin(theta);
        vec[1] = l*sin(phi)*sin(theta);
        vec[2] = l*cos(theta);

        int limAxis = use.axisOfBiggestProjection(vec);
        double c = 10;
        double normOfVec = use.norm(vec);

        //////////////////////////////////////////////////////////////////////////
        //		Generating the sequence of coordinates that will be visited		//
        //////////////////////////////////////////////////////////////////////////

        for (int i = 0; i < repetitions; i++)
        {
            if (i % 2 == 1){
                storagePos[i][0] = pos[0] + vec[0] + c*vec[0] / normOfVec;
                storagePos[i][1] = pos[1] + vec[1] + c*vec[1] / normOfVec;
                storagePos[i][2] = pos[2] + vec[2] + c*vec[2] / normOfVec;
            }

            if (i % 2 == 0){
            }
        }

        //////////////////////////////////////////////////////
        //		Write sequence to file for controle			//
        //////////////////////////////////////////////////////

        use.writeCoordToFile("line3DAbs.txt", storagePos, repetitions);

        //////////////////////////////////////////
        //		Actual cutting procedure 		//
        //////////////////////////////////////////

        //A
        ::gE545.moveTo(storagePos[0][0], storagePos[0][1], storagePos[0][2]);
        ::gE545.setLimits(limAxis, pos[limAxis], pos[limAxis] + vec[limAxis]);

        for (int i = 0; i < repetitions; i++){

            cout<<"i "<<i<<endl;
            ::gE545.moveTo(storagePos[i][0], storagePos[i][1], storagePos[i][2]);

        }
        cout<<"close sh"<<endl;
        ::gE545.closeShutter();
        cout<<"close set vel"<<endl;
        ::gE545.setVelocity(1000, 1000, 1000);
        ::gE545.moveTo(pos[0], pos[1], pos[2]);

    }//else


    cout<<"void figures::line::cutAbsLim3D() LEAVING"<<endl;

}

