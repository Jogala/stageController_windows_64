#ifndef LINE_H
#define LINE_H

#include <QDebug>
#include <QDir>

#include "figures.h"

namespace figures
{

class line : public figures
{
private:
    string storedValuesPath;
    double itsValues[5];

//    double l, phi, velocity, theta;
//    int repetitions;

public:

    void setStoredValuesPath(string newstoredValuesPath ){
        storedValuesPath=newstoredValuesPath;
    }
    string getStoredValuesPath(){

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
        cout<<"line::line() ENTERING"<<endl;
        storedValuesPath="./Stored_Values/line.txt";
        cout<<"line::line() LEAVING"<<endl;
    }
    ~line(){}

};
}
#endif // LINE_H
