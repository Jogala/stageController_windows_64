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

    //////////////////////////////////////////
    //		Actual cutting procedure 		//
    //////////////////////////////////////////

    std::fstream f;
    f << std::fixed;
    f << std::setprecision(5);
    f.open(nameFile, std::fstream::out | std::fstream::trunc);
    f.close();
    f.open(nameFile, std::fstream::out | std::fstream::app);

    f << "MAC BEG " << macroName << std::endl;
    f << "VEL A " << velocity << " B " << velocity << " C " << velocity << std::endl;
    //Open Shutter
    for (int i = 0; i < steps+1; i++){
        f << "MOV A " << storPos[i][0] << " B " << storPos[i][1] << " C " << storPos[i][2] << std::endl;


        if (i == 0){
            f << "DEL " << (R / velocity) * 1000 * 2 << std::endl;
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
    ::gE545.sendMacros(nameFile);

    ::gE545.closeShutter();
    ::gE545.startMacroAndWaitWhileRunning(macroName);

    //########################################################################################################################################################


}
