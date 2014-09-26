#ifndef POLYGON_H
#define POLYGON_H

#include "figures.h"

namespace figures
{

//////////////////////////////
//			polygon			//
//////////////////////////////
class polygon : public figures{

private:

    std::string storedValuesPath;
    double itsValues[6];

    //        double itsR, phi0, velocity;
    //        int steps;
    //        double rotAngleX, rotAngleZ;

public:
    void setStoredValuesPath(std::string newstoredValuesPath ){
        storedValuesPath=newstoredValuesPath;
    }
    std::string getStoredValuesPath(){
        return storedValuesPath;
    }

    void loadValuesFromTextFile();
    void writeValuesToTextFile();

    void setValue(int i, double value);
    double getValue(int i);

    void printMemberVariables();

    void cutAbsViaMacro3D();



    polygon(){
            std::cout<<"polygon::polygon() ENTERING"<<std::endl;
            storedValuesPath="./Stored_Values/poly.txt";
            std::cout<<"polygon::polygon() LEAVING"<<std::endl;
    }

    ~polygon(){

    }

};

}






#endif // POLYGON_H
