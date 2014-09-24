#pragma once
#include "Header.h"

using namespace std;
class usefulFunctions
{
public:
    bool cinAndCheckForDoubleAndLimits(double & xStepSize);
    bool cinAndCheckForDoubleAndLimits(double & xStepSize, double min);
    bool cinAndCheckForDoubleAndLimits(double & xStepSize, double min, double max);
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
    const string numberToString(aNumber x){
        stringstream ss;
        ss << x;
        return ss.str();
    }

    template<class aNumber>
    void assignValueToMember(const char * charArray, aNumber & member, string name){

        aNumber temp;
        string myString(charArray);
        stringstream ss;

        ss.str(myString);
        if (!(ss >> temp)){
            cout << "no new value set for "<<name << endl;
        }
        else{
            member = temp;
            cout <<name<< " = " << member << endl;
        }
        ss.str("");
        ss.clear();

    }

    template<class aNumber>
    void constCharToNumber(const char * charArray, aNumber & number){

        string myString(charArray);
        stringstream ss;

        ss.str(myString);
        if (!(ss >> number)){
            cout << "ERROR:" << endl;
            cout << "constCharToNumber failed" << endl;
        }

    }

    void writeCoordToFile(string name, double storedPos[][3], int length){

//        fstream f;
//        f << fixed;
//        f << setprecision(3);

//        f.open(name, fstream::out | fstream::trunc);
//        f.close();
//        f.open(name, fstream::out | fstream::app);

//        for (int i = 0; i < length; i++){

//            f << storedPos[i][0] << "\t" << storedPos[i][1] << "\t" << storedPos[i][2] << endl;

//        }

//        f.close();
    }
    void writeCoordToFile(string name, vector< vector<double> > &storedPos, int length){

//        fstream f;
//        f << fixed;
//        f << setprecision(3);

//        f.open(name, fstream::out | fstream::trunc);
//        f.close();
//        f.open(name, fstream::out | fstream::app);

//        for (int i = 0; i < length; i++){

//            f << storedPos[i][0] << "\t" << storedPos[i][1] << "\t" << storedPos[i][2] << endl;

//        }

//        f.close();
    }

    template<class aNumber>
    aNumber norm(aNumber v[3]){

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

    usefulFunctions();
    ~usefulFunctions();
};

