#include "line.h"

void    figures::line::loadValuesFromTextFile(){

    std::cout<<"void    figures::line::loadValuesFromTextFile() ENTERING"<<std::endl;

    std::fstream f;

    f.open(storedValuesPath);

    if (f.is_open()) {

        for(auto item : itsValues){
            f>>item;
        }
    }
    f.close();

    std::cout<<"void    figures::line::loadValuesFromTextFile() LEAVING"<<std::endl;
}
void    figures::line::writeValuesToTextFile(){

    std::cout<<"void    figures::line::writeValuesToTextFile() ENTERING"<<std::endl;

    std::fstream f;
    f.open(storedValuesPath);

    std::cout<<"writing values to "<<storedValuesPath<<std::endl;
    for(auto item : itsValues)
    {
        std::cout<<item<<std::endl;
        f<<item<<std::endl;
    }

    f.close();

    std::cout<<"void    figures::line::writeValuesToTextFile() LEAVING"<<std::endl;
}

void    figures::line::setValue(int i, double value){

    itsValues[i]=value;

}
double  figures::line::getValue(int i){

    return itsValues[i];
}

void    figures::line::printMemberVariables(){

    std::cout<<"PRINT MEMBER VARIABLES"<<std::endl;
    int i = 0;
    for(auto item : itsValues){
        std::cout<<i++<<" "<<item<<std::endl;
    }

}


void figures::line::cutAbs3D(){

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"ENTER void figures::line::cutAbs3D()"<<std::endl;


    double l = itsValues[0];
    double phi = itsValues[1];
    double theta= itsValues[2];
    double repetitions= itsValues[3];
    double velocity = itsValues[4];

    if (repetitions < 1){

        std::cout << std::endl;
        std::cout << "ERROR:" << std::endl;
        std::cout << "repetitions has to be >= 1" << std::endl;

    }
    else{

        ::gE545.setVelocity(velocity, velocity, velocity);

        double vec[3];
        auto storagePos = std::vector<std::vector<double>>(repetitions, std::vector<double>(3));

        double pos[3];
        ::gE545.getPositon(pos);

        std::cout<<"########################################################################"<<std::endl;
        std::cout<<"in figures::line::cutAbs3D() get focus values"<<std::endl;
        double focus[3];
        ::gE545.getFocusValues(focus);
        std::cout<<"in figures::line::cutAbs3D() get focus values DONE"<<std::endl;
        std::cout<<"#########################################################################"<<std::endl;

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
            std::cout << " cut number " << i+1 << std::endl;
            ::gE545.moveTo(storagePos[i][0], storagePos[i][1], storagePos[i][2]);

        }
        ::gE545.closeShutter();
        ::gE545.setVelocity(9000, 9000, 9000);
        ::gE545.moveTo(pos[0] +focus[0] + vec[0] / 2, pos[1] + focus[1]+ vec[1] / 2, pos[2] + focus[2]+ vec[2] / 2);
    }//else

    std::cout<<"LEAVE void figures::line::cutAbs3D()"<<std::endl;


}
void figures::line::cutAbsLim3D(){

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"####################################################"<<std::endl;
    std::cout<<"void figures::line::cutAbsLim3D() ENTERING"<<std::endl;

    double l = itsValues[0];
    double phi = itsValues[1];
    double theta= itsValues[2];
    double repetitions= itsValues[3];
    double velocity = itsValues[4];


    if (repetitions < 1){

        std::cout << std::endl;
        std::cout << "ERROR:" << std::endl;
        std::cout << "repetitions has to be >= 1" << std::endl;

    }
    else{


        double vec[3];
        double pos[3];
        double focus[3];
        ::gE545.getFocusValues(focus);

        auto storagePos = std::vector<std::vector<double>>(repetitions+1, std::vector<double>(3));

        ::gE545.getPositon(pos);

        vec[0] = l*cos(phi)*sin(theta);
        vec[1] = l*sin(phi)*sin(theta);
        vec[2] = l*cos(theta);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //      calculate  Velocities s.t. the stage is moving on  a straight line from one point to the other      //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::cout<<"calculate  Velocities s.t. the stage is moving on  a straight line from one point to the other START"<<std::endl;

        double v_x;
        double v_y;
        double v_z;

        if((vec[0]!=0)||(vec[1]!=0)||(vec[2]!=0))
        {
            v_x = (abs(vec[0])/use.norm(vec))*velocity;
            v_y = (abs(vec[1])/use.norm(vec))*velocity;
            v_z = (abs(vec[2])/use.norm(vec))*velocity;

        }else{
            //means that l = 0, so no line is cut, but for being on the safe side we set v_i = 1000.
            v_x=1000;
            v_y=1000;
            v_z=1000;
        }

        std::cout<<"use.norm(vec) = "<<use.norm(vec)<<std::endl;
        std::cout<<" vec: "<<vec[0]<<"  "<<vec[1]<<"  "<<vec[2]<<std::endl;
        std::cout<<" v: "<<v_x<<"  "<<v_y<<"  "<<v_z<<std::endl;

        ::gE545.setVelocity(v_x, v_y, v_z);

        std::cout<<"calculate  Velocities s.t. the stage is moving on  a straight line from one point to the other DONE"<<std::endl;

        //////////////////////////////////////////////////////////////////////////
        //		Generating the sequence of coordinates that will be visited		//
        //////////////////////////////////////////////////////////////////////////

        //c determines how far the stage is moving over the limits.
        double c = 10; //µm
        double normOfVec = use.norm(vec);

        for (int i = 0; i < repetitions+1; i++)
        {
            if (i % 2 == 1){
                storagePos[i][0] = pos[0] + vec[0] + c*vec[0] / normOfVec;
                storagePos[i][1] = pos[1] + vec[1] + c*vec[1] / normOfVec;
                storagePos[i][2] = pos[2] + vec[2] + c*vec[2] / normOfVec;
            }

            if (i % 2 == 0){
                storagePos[i][0] = pos[0] - c*vec[0] / normOfVec;
                storagePos[i][1] = pos[1] - c*vec[1] / normOfVec;
                storagePos[i][2] = pos[2] - c*vec[2] / normOfVec;
            }
        }

        //////////////////////////////////////////////////////
        //		Write sequence to file for controle			//
        //////////////////////////////////////////////////////

        use.writeCoordToFile("./cut_coords/linecutAbsLim3D.txt", storagePos, repetitions+1);

        //////////////////////////////////////////
        //		Actual cutting procedure 		//
        //////////////////////////////////////////

        // limAxis determines on which axis the limit intervall is going to be set.
        int limAxis = use.axisOfBiggestProjection(vec);

        //A
        ::gE545.moveTo(storagePos[0][0], storagePos[0][1], storagePos[0][2]);
        ::gE545.setLimits(limAxis, pos[limAxis-1], pos[limAxis-1] + vec[limAxis-1]);

        for(auto item : vec){
            std::cout<<item<<std::endl;
        }

        std::cout<<"lim axis = "<<limAxis<<std::endl;
        ::gE545.printLimits();

        for (int i = 1; i < repetitions+1; i++){

            ::gE545.moveTo(storagePos[i][0], storagePos[i][1], storagePos[i][2]);

        }
        ::gE545.closeShutter();
        ::gE545.setVelocity(5000, 5000, 5000);

        //center the middle of the line in the laserSpot
        ::gE545.moveTo(pos[0]+vec[0]/2, pos[1]+vec[1]/2, pos[2]+vec[2]/2);
        //move in focus
        ::gE545.moveInFocus();

    }//else
    std::cout<<"void figures::line::cutAbsLim3D() LEAVING"<<std::endl;

}

