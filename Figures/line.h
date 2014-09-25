#ifndef LINE_H
#define LINE_H

#include "figures.h"

namespace figures
{

class line : public figures
{
private:
    std::string storedValuesPath;
    double itsValues[5];

//    double l, phi, velocity, theta;
//    int repetitions;

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

    void cutAbs3D();
    void cutAbsLim3D();


    line(){
        std::cout<<"line::line() ENTERING"<<endl;
        storedValuesPath="./Stored_Values/line.txt";
        std::cout<<"line::line() LEAVING"<<endl;
    }
    ~line(){}

};
}
#endif // LINE_H
