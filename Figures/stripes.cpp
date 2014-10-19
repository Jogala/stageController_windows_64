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

void    figures::stripes::cutAbsLim3D()
{
    std::cout<<"void figures::stripes::cutAbsLim3D() ENTERING"<<std::endl;
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

    printMemberVariables();
    std::cout<<"assign values from array to variables with more concrete names DONE"<<std::endl;

    double phi0RotMat[3][3];
    double xRotMat[3][3];
    double zRotMat[3][3];
    use.setZRotMatrix(phi0RotMat,phi0);
    use.setXRotMatrix(xRotMat,rotAngleX);
    use.setZRotMatrix(zRotMat,rotAngleZ);

    double abstand= b/(anzahlLinien+1);
    double overShot = 5; //µm

    auto posVecR = std::vector<std::vector<double>>(anzahlLinien+2, std::vector<double>(3));
    auto posVecL = std::vector<std::vector<double>>(anzahlLinien+2, std::vector<double>(3));

    double temp[3];
    for(int i = 0; i<anzahlLinien+2;i++)
    {
        temp[0]=a/2;
        temp[1]=b/2 - i*abstand;
        temp[2]=0;

        use.matrixTimesVec(phi0RotMat,temp);
        use.matrixTimesVec(xRotMat,temp);
        use.matrixTimesVec(zRotMat,temp);

        for(int j = 0; j<3;j++)
        {
            posVecR[i][j]=temp[j]+pos[j];
        }

        temp[0]=-a/2;
        temp[1]=b/2 - i*abstand;
        temp[2]=0;

        use.matrixTimesVec(phi0RotMat,temp);
        use.matrixTimesVec(xRotMat,temp);
        use.matrixTimesVec(zRotMat,temp);

        for(int j = 0; j<3;j++)
        {
            posVecL[i][j]=temp[j]+pos[j];
        }


        std::cout<< "posVecL: "<< posVecL[i][0]<<"\t"<<posVecL[i][1]<<"\t"<<posVecL[i][2]<<" posVecR: "<<posVecR[i][0]<<"\t"<<posVecR[i][1]<<"\t"<<posVecR[i][2]<<std::endl;


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

    std::cout<<"+++++++++projections+++++++++"<<std::endl;
    for(int i = 0; i<anzahlLinien+2;i++)
    {
        whichAxis[i]= use.axisOfBiggestProjection(vec[i][0],vec[i][1],vec[i][2]);    
        projectionOntoThisAxis[i]=posVecL[i][whichAxis[i]-1];

        std::cout<<whichAxis[i]<<std::endl;
        std::cout<<projectionOntoThisAxis[i]<<std::endl;

    }
    std::cout<<"+++++++++++++++++++++++++++++"<<std::endl;

    auto normedVec = std::vector<std::vector<double>>(anzahlLinien+2, std::vector<double>(3));
    for(int i = 0; i<anzahlLinien+2;i++)
    {
        normedVec[i][0]=vec[i][0]/use.norm(vec[i][0],vec[i][1],vec[i][2]);
        normedVec[i][1]=vec[i][1]/use.norm(vec[i][0],vec[i][1],vec[i][2]);
        normedVec[i][2]=vec[i][2]/use.norm(vec[i][0],vec[i][1],vec[i][2]);
    }


    ///////////////////////////////////////
    //Write sequence to file for controle//
    ///////////////////////////////////////

    std::fstream fc;
    fc << std::fixed;
    fc << std::setprecision(5);
    fc.open("./cut_coord/stripes_cutAbsLim3D.txt", std::fstream::out | std::fstream::trunc);

    for(int i = 0; i<anzahlLinien+2;i++)
    {
        if(i%2==0){
            fc<<posVecR[i][0]+overShot*normedVec[i][0]<<"\t"<<posVecR[i][1]+overShot*normedVec[i][1]<<"\t"<<posVecR[i][2]+overShot*normedVec[i][2]<<std::endl;
            fc<<whichAxis[i]<<"\t"<<projectionOntoThisAxis[i]<<std::endl;
            fc<<posVecL[i][0]+overShot*normedVec[i][0]<<"\t"<<posVecL[i][1]+overShot*normedVec[i][1]<<"\t"<<posVecL[i][2]+overShot*normedVec[i][2]<<std::endl;

        }else
        {

            fc<<posVecL[i][0]-overShot*normedVec[i][0]<<"\t"<<posVecL[i][1]-overShot*normedVec[i][1]<<"\t"<<posVecL[i][2]-overShot*normedVec[i][2]<<std::endl;
            fc<<whichAxis[i]<<"\t"<<projectionOntoThisAxis[i]<<std::endl;
            fc<<posVecR[i][0]+overShot*normedVec[i][0]<<"\t"<<posVecR[i][1]+overShot*normedVec[i][1]<<"\t"<<posVecR[i][2]+overShot*normedVec[i][2]<<std::endl;
        }

    }
    fc.close();

    std::cout<<"+++++++++++++++++++++++++++++"<<std::endl;
    for(int i = 0; i<anzahlLinien+2;i++)
    {
        std::cout<<posVecL[i][whichAxis[i]-1]<<"\t"<<posVecR[i][whichAxis[i]-1]<<std::endl;
    }
    std::cout<<"+++++++++++++++++++++++++++++"<<std::endl;


    //////////////////////////////////////////
    //		Actual cutting procedure 		//
    //////////////////////////////////////////
    ::gE545.setVelocity(velocity,velocity,velocity);
    for(int i = 0; i<anzahlLinien+2;i++)
    {
        if(i%2==0){
            ::gE545.moveTo
                    (
                        posVecR[i][0]+overShot*normedVec[i][0],
                        posVecR[i][1]+overShot*normedVec[i][1],
                        posVecR[i][2]+overShot*normedVec[i][2]
                    );

            std::cout<<posVecL[i][whichAxis[i]-1]<<"\t"<<posVecR[i][whichAxis[i]-1]<<std::endl;
            ::gE545.setLimits(whichAxis[i],posVecL[i][whichAxis[i]-1],posVecR[i][whichAxis[i]-1]);
            std::cout<<posVecL[i][whichAxis[i]]<<"\t"<<posVecR[i][whichAxis[i]]<<std::endl;
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

            std::cout<<posVecL[i][whichAxis[i]-1]<<"\t"<<posVecR[i][whichAxis[i]-1]<<std::endl;
            ::gE545.setLimits(whichAxis[i],posVecL[i][whichAxis[i]-1],posVecR[i][whichAxis[i]-1]);
            std::cout<<posVecL[i][whichAxis[i]-1]<<"\t"<<posVecR[i][whichAxis[i]-1]<<std::endl;
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
    //center the figure around the laserSpot
    ::gE545.moveTo(pos[0],pos[1],pos[2]);
    //move figure in focus
    ::gE545.moveInFocus();

    std::cout<<"void figures::stripes::cutAbsLim3D() ENTERING"<<std::endl;

}

