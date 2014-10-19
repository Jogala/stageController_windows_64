#ifndef USEFULFUNCTIONS_H
#define USEFULFUNCTIONS_H

#include "./GlobalVariables.h"
#include "./Header.h"

class usefulFunctions
{
private:
    double pi = 3.1415926535897932384626;

public:
    bool cinAndCheckForDoubleAndLimits(double & xStepSize);
    bool cinAndCheckForDoubleAndLimits(double & xStepSize, double minima);
    bool cinAndCheckForDoubleAndLimits(double & xStepSize, double minima, double maxima);
    void cinAndCheckForDouble(double & xStepSize);
    bool qValueInLimits(double value);
    bool qValuesInLimits(double value1, double value2);

    void radToDegByRef(double &phi){

        phi = (phi / (2 * pi)) * 360;

    }
    void degToRadByRef(double &phi){
        phi = (phi / 360) * (2 * pi);
    }
    double radToDegByValue(double phi){

        phi = (phi / (2 * pi)) * 360;

        return phi;
    }
    double degToRadByValue(double phi){
        phi = (phi / 360) * (2 * pi);
        return phi;
    }

    //theta = around x axis 0<=theta<=pi
    //phi = around z axis arbitrary
    void setXRotMatrix(double rotMatX[3][3],double rotAngleX){

        //Rotation matrix X
        rotMatX[0][0] = 1;
        rotMatX[0][1] = 0;
        rotMatX[0][2] = 0;

        rotMatX[1][0] = 0;
        rotMatX[1][1] = cos(rotAngleX);
        rotMatX[1][2] = -sin(rotAngleX);

        rotMatX[2][0] = 0;
        rotMatX[2][1] = sin(rotAngleX);
        rotMatX[2][2] = cos(rotAngleX);

    }

    void setZRotMatrix(double rotMatZ[3][3],double rotAngleZ){

        //Rotation matrix Z
        rotMatZ[0][0] = cos(rotAngleZ);
        rotMatZ[0][1] = -sin(rotAngleZ);
        rotMatZ[0][2] = 0;

        rotMatZ[1][0] = sin(rotAngleZ);
        rotMatZ[1][1] = cos(rotAngleZ);
        rotMatZ[1][2] = 0;

        rotMatZ[2][0] = 0;
        rotMatZ[2][1] = 0;
        rotMatZ[2][2] = 1;

    }

    void setRotMatrices(double rotMatX[3][3], double rotMatZ[3][3], double rotAngleX, double rotAngleZ){

        //Rotation matrix X
        rotMatX[0][0] = 1;
        rotMatX[0][1] = 0;
        rotMatX[0][2] = 0;

        rotMatX[1][0] = 0;
        rotMatX[1][1] = cos(rotAngleX);
        rotMatX[1][2] = -sin(rotAngleX);

        rotMatX[2][0] = 0;
        rotMatX[2][1] = sin(rotAngleX);
        rotMatX[2][2] = cos(rotAngleX);

        //Rotation matrix Z
        rotMatZ[0][0] = cos(rotAngleZ);
        rotMatZ[0][1] = -sin(rotAngleZ);
        rotMatZ[0][2] = 0;

        rotMatZ[1][0] = sin(rotAngleZ);
        rotMatZ[1][1] = cos(rotAngleZ);
        rotMatZ[1][2] = 0;

        rotMatZ[2][0] = 0;
        rotMatZ[2][1] = 0;
        rotMatZ[2][2] = 1;

    }




    void matrixTimesVec(double a[3][3], double &x1, double &x2, double& x3 )
    {

        double v[3];
        v[0] = x1;
        v[1] = x2;
        v[2] = x3;

        double x[3];
        x[0] = 0;
        x[1] = 0;
        x[2] = 0;

        for (int i = 0; i < 3; i++){

            for (int j = 0; j < 3; j++){
                x[i] = x[i] + a[i][j] * v[j];
            }

        }


        x1 = x[0];
        x2 = x[1];
        x3 = x[2];

    }





    void matrixTimesVec(double a[3][3], double v[3]){

        double x[3];
        x[0] = 0;
        x[1] = 0;
        x[2] = 0;

        for (int i = 0; i < 3; i++){

            for (int j = 0; j < 3; j++){
                x[i] = x[i] + a[i][j] * v[j];
            }

        }
        v[0] = x[0];
        v[1] = x[1];
        v[2] = x[2];

    }

    template<class aNumber>
    const std::string numberToString(aNumber x){
        std::stringstream ss;
        ss << x;
        return ss.str();
    }

    template<class aNumber>
    void assignValueToMember(const char * charArray, aNumber & member, std::string name){

        aNumber temp;
        std::string myString(charArray);
        std::stringstream ss;

        ss.str(myString);
        if (!(ss >> temp)){
            std::cout << "no new value set for "<<name << std::endl;
        }
        else{
            member = temp;
            std::cout <<name<< " = " << member << std::endl;
        }
        ss.str("");
        ss.clear();

    }

    template<class aNumber>
    void constCharToNumber(const char * charArray, aNumber & number){

        std::string myString(charArray);
        std::stringstream ss;

        ss.str(myString);
        if (!(ss >> number)){
            std::cout << "ERROR:" << std::endl;
            std::cout << "constCharToNumber failed" << std::endl;
        }

    }

    void writeCoordToFile(std::string name, double storedPos[][3], int length){

        std::fstream f;
        f << std::fixed;
        f << std::setprecision(3);

        f.open(name, std::fstream::out | std::fstream::trunc);
        f.close();
        f.open(name, std::fstream::out | std::fstream::app);

        for (int i = 0; i < length; i++){

            f << storedPos[i][0] << "\t" << storedPos[i][1] << "\t" << storedPos[i][2] << std::endl;

        }

        f.close();
    }
    void writeCoordToFile(std::string name, std::vector< std::vector<double> > &storedPos, int length){

        std::fstream f;
        f << std::fixed;
        f << std::setprecision(3);

        f.open(name, std::fstream::out | std::fstream::trunc);
        f.close();
        f.open(name, std::fstream::out | std::fstream::app);

        for (int i = 0; i < length; i++){

            f << storedPos[i][0] << "\t" << storedPos[i][1] << "\t" << storedPos[i][2] << std::endl;

        }

        f.close();
    }

    template<class aNumber>
    aNumber norm(aNumber v[3]){

        return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    }

    template<class aNumber>
    aNumber norm(aNumber x1,aNumber x2, aNumber x3){

        aNumber v[3];
        v[0]=x1;
        v[1]=x2;
        v[2]=x3;

        return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    }

    template<class aNumber>
    int axisOfBiggestProjection(aNumber v[3]){
        aNumber w[3];
        w[0] = v[0] * v[0];
        w[1] = v[1] * v[1];
        w[2] = v[2] * v[2];

        int j = 0;
        for (int i = 1; i < 3; i++){
            if (w[0] < w[i]){
                j = i;
                w[0] = w[i];
            }
        }

        return j+1;
        //1 for x etc...

    }

    template<class aNumber>
    int axisOfBiggestProjection(const aNumber x1,const aNumber x2,const aNumber x3)
    {

        aNumber v[3];
        v[0]=x1;
        v[1]=x2;
        v[2]=x3;
        aNumber w[3];
        w[0] = v[0] * v[0];
        w[1] = v[1] * v[1];
        w[2] = v[2] * v[2];

        int j = 0;
        for (int i = 1; i < 3; i++){
            if (w[0] < w[i]){
                j = i;
                w[0] = w[i];
            }
        }

        return j+1;
        //1 for x etc...
    }
    usefulFunctions();
    ~usefulFunctions();
};

#endif
