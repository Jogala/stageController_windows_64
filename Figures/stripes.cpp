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
    std::cout<<"assign values from array to variables with more concrete names DONE"<<std::endl;

    double phi0RotMat[3][3];
    double xRotMat[3][3];
    double zRotMat[3][3];
    use.setZRotMatrix(phi0RotMat,phi0);
    use.setXRotMatrix(xRotMat,rotAngleX);
    use.setZRotMatrix(zRotMat,rotAngleZ);

    double abstand= b/(anzahlLinien+1);
    double overShot = 10; //µm

    auto posVecR = std::vector<std::vector<double>>(anzahlLinien+2, std::vector<double>(3));
    auto posVecL = std::vector<std::vector<double>>(anzahlLinien+2, std::vector<double>(3));

    ///////////////////////////////////////////////////////////
    //      generate the coordinates of the  stripes         //
    ///////////////////////////////////////////////////////////

    std::cout<<" generate the coordinates of the  stripes START"<<std::endl;
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
    }
    std::cout<<" generate the coordinates of the  stripes DONE"<<std::endl;

    ////////////////////////////////////////////////////////////////////
    //      determine the axis on which the limits will be changed    //
    ////////////////////////////////////////////////////////////////////

    double vec[3];

    vec[0]=posVecR[0][0]-posVecL[0][0];
    vec[1]=posVecR[0][1]-posVecL[0][1];
    vec[2]=posVecR[0][2]-posVecL[0][2];


    int whichAxis=use.axisOfBiggestProjection(vec);

    //////////////////////////////////////////////////////////////////////////////
    //     create a normed vector pointing in the direction of the stripes      //
    //////////////////////////////////////////////////////////////////////////////

    double normedVec[3];

    normedVec[0]=vec[0]/use.norm(vec);
    normedVec[1]=vec[1]/use.norm(vec);
    normedVec[2]=vec[2]/use.norm(vec);

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
            fc<<posVecR[i][0]+overShot*normedVec[0]<<"\t"<<posVecR[i][1]+overShot*normedVec[1]<<"\t"<<posVecR[i][2]+overShot*normedVec[2]<<std::endl;
            fc<<posVecL[i][0]+overShot*normedVec[0]<<"\t"<<posVecL[i][1]+overShot*normedVec[1]<<"\t"<<posVecL[i][2]+overShot*normedVec[2]<<std::endl;

        }else
        {

            fc<<posVecL[i][0]-overShot*normedVec[0]<<"\t"<<posVecL[i][1]-overShot*normedVec[1]<<"\t"<<posVecL[i][2]-overShot*normedVec[2]<<std::endl;
            fc<<posVecR[i][0]+overShot*normedVec[0]<<"\t"<<posVecR[i][1]+overShot*normedVec[1]<<"\t"<<posVecR[i][2]+overShot*normedVec[2]<<std::endl;
        }

    }
    fc.close();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //      calculate  Velocities s.t. the stage is moving on  a straight line from one point to the other      //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    double velVec[3];

    vec[0] = abs(posVecR[0][0]-posVecL[0][0])+2*abs(overShot*normedVec[0]);
    vec[1] = abs(posVecR[0][1]-posVecL[0][1])+2*abs(overShot*normedVec[1]);
    vec[2] = abs(posVecR[0][2]-posVecL[0][2])+2*abs(overShot*normedVec[2]);

    if((vec[0]!=0)||(vec[1]!=0)||(vec[2]!=0))
    {
        velVec[0] = (abs(vec[0])/use.norm(vec))*velocity;
        velVec[1] = (abs(vec[1])/use.norm(vec))*velocity;
        velVec[2] = (abs(vec[2])/use.norm(vec))*velocity;

    }else{
        //means that a = 0, so no line is cut, but for being on the safe side we set v_i = 1000.
        velVec[0]=1000;
        velVec[1]=1000;
        velVec[2]=1000;
    }

    double velVecGoToNextLine[3];

    vec[0] = abs(posVecL[1][0]-posVecL[0][0]);
    vec[1] = abs(posVecR[1][1]-posVecL[0][1]);
    vec[2] = abs(posVecR[1][2]-posVecL[0][2]);

    if((vec[0]!=0)||(vec[1]!=0)||(vec[2]!=0))
    {
        velVecGoToNextLine[0] = (abs(vec[0])/use.norm(vec))*velocity;
        velVecGoToNextLine[1] = (abs(vec[1])/use.norm(vec))*velocity;
        velVecGoToNextLine[2] = (abs(vec[2])/use.norm(vec))*velocity;

    }else{
        //means that b = 0, so no line is cut, but for being on the safe side we set v_i = 1000.
        velVecGoToNextLine[0]=1000;
        velVecGoToNextLine[1]=1000;
        velVecGoToNextLine[2]=1000;
    }


    //////////////////////////////////////////
    //		Actual cutting procedure 		//
    //////////////////////////////////////////
    double limLeft;
    double limRight;

    ::gE545.setVelocity(2000,2000,2000);

    ::gE545.moveTo
            (
                posVecR[0][0]+overShot*normedVec[0],
                posVecR[0][1]+overShot*normedVec[1],
                posVecR[0][2]+overShot*normedVec[2]
            );


    ::gE545.setLimits(whichAxis,posVecL[0][whichAxis-1],posVecR[0][whichAxis-1]);
    ::gE545.setVelocity(velVec);

    ::gE545.moveTo
            (
                posVecL[0][0]-overShot*normedVec[0],
                posVecL[0][1]-overShot*normedVec[1],
                posVecL[0][2]-overShot*normedVec[2]
            );


    for(int i = 1; i<anzahlLinien+2;i++)
    {


        if(i%2==1)
        {
            //////////////////////////////////////////
            //from left to right side  L ----> R    //
            //////////////////////////////////////////

            ::gE545.setVelocity(velVecGoToNextLine);

            //ordering Intervall boarder points. We need that for determining if next left point of the limits lies in the limits.
            if(posVecL[i-1][whichAxis-1]<posVecR[i-1][whichAxis-1])
            {
                limLeft = posVecL[i-1][whichAxis-1];
                limRight = posVecR[i-1][whichAxis-1];
            }else
            {
                limLeft =  posVecR[i-1][whichAxis-1];
                limRight = posVecL[i-1][whichAxis-1];
            }

            //if the left point of the next Line lies in the old limits (that would cause the shutter to open when we move to the next line what we don't want)
            if(((posVecL[i][whichAxis-1]-overShot*normedVec[whichAxis-1])>= limLeft)&&((posVecL[i][whichAxis-1]-overShot*normedVec[whichAxis-1])<= limRight))
            {
                //we change the limits first
                ::gE545.setLimits(whichAxis,posVecL[i][whichAxis-1],posVecR[i][whichAxis-1]);
                //and then move to the next line
                ::gE545.moveTo
                        (
                            posVecL[i][0]-overShot*normedVec[0],
                            posVecL[i][1]-overShot*normedVec[1],
                            posVecL[i][2]-overShot*normedVec[2]
                        );
            }
            else
            {
                //we move first to the next line
                ::gE545.moveTo
                        (
                            posVecL[i][0]-overShot*normedVec[0],
                            posVecL[i][1]-overShot*normedVec[1],
                            posVecL[i][2]-overShot*normedVec[2]
                        );
                //and then change the limits
                ::gE545.setLimits(whichAxis,posVecL[i][whichAxis-1],posVecR[i][whichAxis-1]);
            }


            ::gE545.setVelocity(velVec);

            ::gE545.moveTo
                    (
                        posVecR[i][0]+overShot*normedVec[0],
                        posVecR[i][1]+overShot*normedVec[1],
                        posVecR[i][2]+overShot*normedVec[2]
                    );

        }else
        {
            //////////////////////////////////////////
            //from rigth to left side  L <---- R    //
            //////////////////////////////////////////

            ::gE545.setVelocity(velVecGoToNextLine);

            //ordering Intervall boarder points. We need that for determining if next left point of the limits lies in the limits.
            if(posVecL[i-1][whichAxis-1]<posVecR[i-1][whichAxis-1])
            {
                limLeft = posVecL[i-1][whichAxis-1];
                limRight = posVecR[i-1][whichAxis-1];
            }else
            {
                limLeft =  posVecR[i-1][whichAxis-1];
                limRight = posVecL[i-1][whichAxis-1];
            }

            //if the right point of the next Line lies in the old limits (that would cause the shutter to open when we move to the next line what we don't want)
            if(((posVecR[i][whichAxis-1]+overShot*normedVec[whichAxis-1])>= limLeft)&&((posVecR[i][whichAxis-1]+overShot*normedVec[whichAxis-1])<= limRight))
            {
                //we change the limits first
                ::gE545.setLimits(whichAxis,posVecL[i][whichAxis-1],posVecR[i][whichAxis-1]);
                //and then move to the next line
                ::gE545.moveTo
                        (
                            posVecR[i][0]+overShot*normedVec[0],
                            posVecR[i][1]+overShot*normedVec[1],
                            posVecR[i][2]+overShot*normedVec[2]
                        );

            }else
            {
                //we move first to the next line
                ::gE545.moveTo
                        (
                            posVecR[i][0]+overShot*normedVec[0],
                            posVecR[i][1]+overShot*normedVec[1],
                            posVecR[i][2]+overShot*normedVec[2]
                        );
                //and then change the limits
                ::gE545.setLimits(whichAxis,posVecL[i][whichAxis-1],posVecR[i][whichAxis-1]);
            }


            ::gE545.setVelocity(velVec);

            ::gE545.moveTo
                    (
                        posVecL[i][0]-overShot*normedVec[0],
                        posVecL[i][1]-overShot*normedVec[1],
                        posVecL[i][2]-overShot*normedVec[2]
                    );

        }

    }


    ::gE545.closeShutter();

    ::gE545.setVelocity(9900,9900,9900);
    //center the figure around the laserSpot
    ::gE545.moveTo(pos[0],pos[1],pos[2]);
    //move figure in focus
    ::gE545.moveInFocus();

    std::cout<<"void figures::stripes::cutAbsLim3D() LEAVING"<<std::endl;
}

