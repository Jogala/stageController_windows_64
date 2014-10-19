#include "polygon.h"


void    figures::polygon::loadValuesFromTextFile()
{

    std::fstream f;

    f.open(storedValuesPath);

    if (f.is_open()) {

        for(auto item : itsValues){
            f>>item;
        }

    }
    f.close();

}
void    figures::polygon::writeValuesToTextFile(){
    std::cout<<"void    figures::polygon::writeValuesToTextFile() ENTERING"<<std::endl;

   std::fstream f;
   f.open(storedValuesPath);

   std::cout<<"writing values to "<<storedValuesPath<<std::endl;
   for(auto item : itsValues)
   {
       std::cout<<item<<std::endl;
       f<<item<<std::endl;
   }

   f.close();
   std::cout<<"void    figures::polygon::writeValuesToTextFile() LEAVING"<<std::endl;

}

void    figures::polygon::setValue(int i, double value){

    itsValues[i]=value;

}
double  figures::polygon::getValue(int i){

    return itsValues[i];
}

void    figures::polygon::printMemberVariables(){

    int i = 0;
    for(auto item : itsValues){
        std::cout<<i++<<" "<<item<<std::endl;
    }

}

void    figures::polygon::cutAbsViaMacro3D(){

    //////////////////////////////////////////
    //                 Set up               //
    //////////////////////////////////////////

    double R=itsValues[0];
    int    steps=itsValues[1];
    double phi0=itsValues[2];
    double rotAngleX=itsValues[3];
    double rotAngleZ=itsValues[4];
    double velocity = itsValues[5];

    double focus[3];
    ::gE545.getFocusValues(focus);
    double pos[3];
    ::gE545.getPositon(pos);

    double deltaAlpha = (2 * pi) / steps;
    double vec[3];
    auto storPos = std::vector<std::vector<double>>(steps + 1, std::vector<double>(3));

    double delay = 1000 * (sin(deltaAlpha / 2) * 2 * R*delayFactor) / velocity;

    std::string macroName = "macroPoly";
    std::string nameFile = "macroPoly.txt";

    double phi0RotMat[3][3];
    double xRotMat[3][3];
    double zRotMat[3][3];

    use.setZRotMatrix(phi0RotMat,phi0);
    use.setXRotMatrix(xRotMat,rotAngleX);
    use.setZRotMatrix(zRotMat,rotAngleZ);

    //########################################################################################################################################################

    //////////////////////////////////////////
    //		Generating the coordinates		//
    //////////////////////////////////////////
    for (int i = 0; i < steps+1; i++){

        vec[0] = R*cos(deltaAlpha*i + pi / 2);
        vec[1] = R*sin(deltaAlpha*i + pi / 2);
        vec[2] = 0;

        use.matrixTimesVec(phi0RotMat, vec);
        use.matrixTimesVec(xRotMat, vec);
        use.matrixTimesVec(zRotMat, vec);

        storPos[i][0] = vec[0] + pos[0];
        storPos[i][1] = vec[1] + pos[1];
        storPos[i][2] = vec[2] + pos[2];
    }

    //########################################################################################################################################################

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //      calculate  Velocities s.t. the stage is moving on  a straight line from one point to the other      //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout<<"calculate  Velocities s.t. the stage is moving on  a straight line from one point to the other START"<<std::endl;

    auto velVec = std::vector<std::vector<double>>(steps, std::vector<double>(3));
    for (int i = 0; i <steps; i++)
    {
        for(int j = 0; j<3; j++)
        {
            vec[j]=storPos[i+1][j]-storPos[i][j];
        }

        if((vec[0]!=0)||(vec[1]!=0)||(vec[2]!=0))
        {
            velVec[i][0] = (abs(vec[0])/use.norm(vec))*velocity;
            velVec[i][1] = (abs(vec[1])/use.norm(vec))*velocity;
            velVec[i][2] = (abs(vec[2])/use.norm(vec))*velocity;
        }else{
            //means that a = 0 or b = 0, so no line is cut, but for being on the safe side we set v_i = 1000.
            velVec[i][1]=1000;
            velVec[i][2]=1000;
            velVec[i][3]=1000;
        }
    }
    std::cout<<"calculate  Velocities s.t. the stage is moving on  a straight line from one point to the other DONE"<<std::endl;

    //########################################################################################################################################################

    ///////////////////////////////////////
    //Write sequence to file for controle//
    ///////////////////////////////////////
    std::fstream fc;
    fc << std::fixed;
    fc << std::setprecision(5);
    fc.open(nameFile, std::fstream::out | std::fstream::trunc);
    fc.close();
    fc.open(nameFile, std::fstream::out | std::fstream::app);

    for (int i = 0; i < steps + 1; i++){
        for (int j = 0; j < 3; j++){

            fc << storPos[i][j] << std::endl;

        }
    }

    use.writeCoordToFile("cutAbsMacro3D_Coord.txt", storPos, steps + 1);
    fc.close();
    std::cout << "coordinates written to file:" << "cutAbsMacro3D_Coord.txt" << std::endl;

    //########################################################################################################################################################

    //////////////////////////////////////////////////////////////
    //		Create Macro text file and send it to the stage		//
    //////////////////////////////////////////////////////////////

    std::fstream f;
    f << std::fixed;
    f << std::setprecision(5);
    f.open(nameFile, std::fstream::out | std::fstream::trunc);
    f.close();
    f.open(nameFile, std::fstream::out | std::fstream::app);

    f << "MAC BEG " << macroName << std::endl;
    f << "VEL A " << 5000 << " B " << 5000 << " C " << 5000 << std::endl;

    for (int i = 0; i < steps+1; i++){


        if(i!=0)
        {
            f << "VEL A " << velVec[i-1][0] << " B " << velVec[i-1][1] << " C " << velVec[i-1][2] << std::endl;
        }

        f << "MOV A " << storPos[i][0] << " B " << storPos[i][1] << " C " << storPos[i][2] << std::endl;

        if (i == 0){
            //Move out from center to "polygon path" needs of course a other delay...
            f << "DEL " << (R / velocity) * 1000 * 2 << std::endl;
            //open Shutter
            f << ::gE545.setLimitsMacro(1, 0, 200, 0, 0);
        }
        else{
            f << "DEL " << delay << std::endl;
        }
    }
    //Close Shutter
    f << ::gE545.setLimitsMacro(1, 0, 0, 0, 200);
    f << "VEL A " << "9000" << " B " << "9000" << " C " << "9000" << std::endl;
    f << "MOV A " << pos[0] + focus[0] << " B " << pos[1] + focus[1]<< " C " << pos[2] + focus[2] << std::endl;
    f << "DEL 1000" << std::endl;
    f << "MAC END" << std::endl;
    f.close();

    std::cout << "Macro written to file:" << nameFile << std::endl;
    std::cout << "SENDING MACRO TO CONTROLLER..." << std::endl;
    ::gE545.sendMacro(nameFile);
    ::gE545.closeShutter();
    ::gE545.startMacroAndWaitWhileRunning(macroName);

    //I don't know why... but one has to reconnect after uploading a macro. Otherwise the stage shows a wired behaviour.
    ::gE545.reconnect();

    //#######################################################################################################################################################
}
