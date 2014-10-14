#ifndef STRIPES_H
#define STRIPES_H

#include "figures.h"

namespace figures
{
class stripes : public figures
{
private:
    std::string storedValuesPath;
    double itsValues[6];

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

    void cutAbsLim3D();





    stripes(){
        std::cout<<"stripes::stripes() ENTERING"<<std::endl;
        storedValuesPath="./Stored_Values/stripes.txt";
        std::cout<<"stripes::stripes() LEAVING"<<std::endl;
    }
};
}
#endif // STRIPES_H
