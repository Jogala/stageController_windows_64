#include "stripes.h"

void    figures::stripes::loadValuesFromTextFile(){

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
void    figures::stripes::writeValuesToTextFile(){

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

void    figures::stripes::setValue(int i, double value){

    itsValues[i]=value;

}
double  figures::stripes::getValue(int i){

    return itsValues[i];
}

void    figures::stripes::printMemberVariables(){

    std::cout<<"PRINT MEMBER VARIABLES"<<std::endl;
    int i = 0;
    for(auto item : itsValues){
        std::cout<<i++<<" "<<item<<std::endl;
    }

}

void figures::stripes::cutAbsLim3D()
{
    double pos[3];
    ::gE545.getPositon(pos);
    ::gE545.closeShutter();
    double focus[3];
    ::gE545.getFocusValues(focus);

    std::cout<<"assign values from array to variables with more concrete names START"<<std::endl;
    double a=itsValues[0];
    double b=itsValues[1];
    double phi0=itsValues[2];
    double rotAngleX=itsValues[3];
    double rotAngleZ=itsValues[4];
    int anzahlLinien = itsValues[5];
    double velocity = itsValues[6];
    std::cout<<"assign values from array to variables with more concrete names DONE"<<std::endl;

    double abstand= b/anzahlLinien;
    double overShot = 5; //µm

    auto posVecR = std::vector<std::vector<double>>(anzahlLinien+2, std::vector<double>(3));
    auto posVecL = std::vector<std::vector<double>>(anzahlLinien+2, std::vector<double>(3));

    for(int i = 0; i<anzahlLinien+2;i++)
    {
        posVecR[i][0]=a/2   +           pos[0];
        posVecR[i][1]=b/2 - i*abstand + pos[1];
        posVecR[i][2]=                  pos[2];

        posVecL[i][0]=-a/2  +           pos[0];
        posVecL[i][1]=b/2 - i*abstand+  pos[1];
        posVecL[i][2]=                  pos[2];
    }

    auto vec = std::vector<std::vector<double>>(anzahlLinien+2, std::vector<double>(3));
    for(int i = 0; i<anzahlLinien+2;i++)
    {
        vec[i][0]=posVecR[i][0]-posVecL[i][0];
        vec[i][1]=posVecR[i][1]-posVecL[i][1];
        vec[i][2]=posVecR[i][2]-posVecL[i][2];
    }

    auto whichAxis = std::vector<int>(anzahlLinien+2);
    auto projectionOntoThisAxis = std::vector<double>(anzahlLinien+2);

    for(int i = 0; i<anzahlLinien+2;i++)
    {
        whichAxis[i]= use.axisOfBiggestProjection(vec[i][0],vec[i][1],vec[i][2]);
        projectionOntoThisAxis[i]=vec[i][whichAxis[i]];
    }

    auto normedVec = std::vector<std::vector<double>>(anzahlLinien+2, std::vector<double>(3));
    for(int i = 0; i<anzahlLinien+2;i++)
    {
        normedVec[i][0]=vec[i][0]/use.norm(vec[i][0],vec[i][1],vec[i][2]);
        normedVec[i][1]=vec[i][1]/use.norm(vec[i][0],vec[i][1],vec[i][2]);
        normedVec[i][2]=vec[i][2]/use.norm(vec[i][0],vec[i][1],vec[i][2]);
    }


    for(int i = 0; i<anzahlLinien+2;i++)
    {
        if(i%2==0){
            ::gE545.moveTo
                    (
                        posVecR[i][0]+overShot*normedVec[i][0],
                        posVecR[i][1]+overShot*normedVec[i][1],
                        posVecR[i][2]+overShot*normedVec[i][2]
                    );

            ::gE545.setLimits(whichAxis[i],-projectionOntoThisAxis[i],+projectionOntoThisAxis[i]);

            ::gE545.moveTo
                    (
                        posVecL[i][0]-overShot*normedVec[i][0],
                        posVecL[i][1]-overShot*normedVec[i][1],
                        posVecL[i][2]-overShot*normedVec[i][2]
                    );
        }else
        {
            ::gE545.moveTo
                    (
                        posVecL[i][0]-overShot*normedVec[i][0],
                        posVecL[i][1]-overShot*normedVec[i][1],
                        posVecL[i][2]-overShot*normedVec[i][2]
                    );

            ::gE545.setLimits(whichAxis[i],-projectionOntoThisAxis[i],+projectionOntoThisAxis[i]);

            ::gE545.moveTo
                    (
                        posVecR[i][0]+overShot*normedVec[i][0],
                        posVecR[i][1]+overShot*normedVec[i][1],
                        posVecR[i][2]+overShot*normedVec[i][2]
                    );
        }

    }


    ::gE545.closeShutter();
    ::gE545.setVelocity(9900,9900,9900);
    ::gE545.moveTo(pos[0] + focus[0], pos[1] + focus[1], pos[2] + focus[2]);
    std::cout<<"Leaving void figures::rectangle::cutAbs3D()"<<std::endl;
}

