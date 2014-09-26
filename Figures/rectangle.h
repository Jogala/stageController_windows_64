#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "figures.h"

namespace figures
{

class rectangle : public figures
{
private:

    double itsValues[6];

    std::string storedValuesPath;
    
    //leaveOrSwap leaves a and b unchanged if -45<=phi<=45 or 135<=phi<=225
    //and adjusts phi
    void leaveOrSwapAndAdjustPhi(double &phi, double &a, double &b);
    
public:
    std::string getStoredValuesPath(){
        return storedValuesPath;
    }
    void setStoredValuesPath(std::string newstoredValuesPath ){
        storedValuesPath=newstoredValuesPath;
    }

    void cutAbs3D();

    void   setValue(int i, double value);
    double getValue(int i);

    void writeValuesToTextFile();
    void loadValuesFromTextFile();

    void printMemberVariables();


    
    rectangle(){
        std::cout<<"rectangle::rectangle() ENTERING"<<std::endl;
        storedValuesPath = "./Stored_Values/rec.txt" ;
        std::cout<<"rectangle::rectangle() LEAVING"<<std::endl;
    }
    ~rectangle(){}
    
};
}
#endif
