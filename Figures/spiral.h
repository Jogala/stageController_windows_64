#ifndef SPIRAL_H
#define SPIRAL_H
#include "figures.h"

namespace figures{
	//////////////////////////////
	//			spiral			//
	//////////////////////////////
	class spiral : public figures{
	private:

        std::string storedValuesPath;
        double itsValues[8];

//		double itsR, phi0, velocity;
//		int steps;
//		double rotAngleX, rotAngleZ;
//		int sectors;
//		double radiusRatio;

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

        void setValue(double RIn, double phi0In, double rotAngleXIn, double rotAngleZIn, int stepsIn, double velocityIn);

        void cutAbsMacroSpiral3D();

		spiral(){
            std::cout<<"spiral::spiral() ENTERING"<<std::endl;
            storedValuesPath="./Stored_Values/spiral.txt";
            std::cout<<"spiral::spiral() LEAVING"<<std::endl;
		}

		~spiral(){

		}

	};
}
#endif
