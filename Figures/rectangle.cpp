#include "rectangle.h"


void    figures::rectangle::loadValuesFromTextFile()
{
    std::fstream f;

    f.open(storedValuesPath);

    if (f.is_open()) {

        for(auto item : itsValues){
            f>>item;
        }

    }
    f.close();

}
void    figures::rectangle::writeValuesToTextFile(){
   std::cout<<"void    figures::rectangle::writeValuesToTextFile()"<<std::endl;

   std::fstream f;
   f.open(storedValuesPath);

   if(!(f.is_open()))
   {
     std::cout<<"failed to open "<< storedValuesPath <<std::endl;
   }else
   {

   std::cout << storedValuesPath <<" opened successfully "<<std::endl;

   for(auto item : itsValues)
   {
       f<<item<<std::endl;
   }

   f.close();
   std::cout << storedValuesPath <<" closed "<<std::endl;
   }

   std::cout<<"Leaving void    figures::rectangle::writeValuesToTextFile()"<<std::endl;
}

void    figures::rectangle::setValue(int i, double value){

    std::cout<<"void    figures::rectangle::setValue(int i, double value)"<<std::endl;
    itsValues[i]=value;
    std::cout<<"itsValue("<<i<<") = "<<itsValues[i]<<std::endl;

}
double  figures::rectangle::getValue(int i){

    return itsValues[i];
}

void    figures::rectangle::printMemberVariables(){

    int i = 0;
    for(auto item : itsValues){
        std::cout<<i++<<" "<<item<<std::endl;
    }

}

void figures::rectangle::cutAbs3D(){
std::cout<<"void figures::rectangle::cutAbs3D()"<<std::endl;

std::cout<<"assign values from array to variables with more concrete names START"<<std::endl;
    double a=itsValues[0];
    double b=itsValues[1];
    double phi0=itsValues[2];
    double rotAngleX=itsValues[3];
    double rotAngleZ=itsValues[4];
    double velocity = itsValues[5];
std::cout<<"assign values from array to variables with more concrete names DONE"<<std::endl;

    if ((a <= 0) || (b <= 0))
    {
		std::cout << "ERROR:" << std::endl;
		std::cout << "a <= 0 or b <= 0 are no exaptable values for a rectangle " << std::endl;
	}
	else{

        ::gE545.setVelocity(velocity, velocity, velocity);

        double deltaPhi[2];
        double R;
        double storagePos[5][3];
        double vec[3];
        int moves = 5;

		double xRotMat[3][3];
		double zRotMat[3][3];
        use.setRotMatrices(xRotMat, zRotMat, rotAngleX, rotAngleZ);

        double focus[3];
        ::gE545.getFocusValues(focus);
        double pos[3];
        ::gE545.getPositon(pos);


		//////////////////////////////////////////////////////////////////////////
		//		Generating the sequence of coordinates that will be visited		//
		//////////////////////////////////////////////////////////////////////////
        std::cout<<"Generating the sequence of coordinates that will be visited START"<<std::endl;

		R = 0.5*sqrt(a*a + b*b);
		deltaPhi[0] = 2 * atan(b / a);
		deltaPhi[1] = 2 * atan(a / b);

		double deltaPhiSum = phi0 - deltaPhi[0] / 2.0;


		//A
		//##################################
		vec[0] = R*cos(deltaPhiSum);
		vec[1] = R*sin(deltaPhiSum);
		vec[2] = 0;

		use.matrixTimesVec(xRotMat, vec);
		use.matrixTimesVec(zRotMat, vec);

		storagePos[0][0] = vec[0] + pos[0];
		storagePos[0][1] = vec[1] + pos[1];
		storagePos[0][2] = vec[2] + pos[2];
		//##################################

		//B, C, D, A 
		for (int i = 1; i <moves; i++){

			deltaPhiSum = deltaPhiSum + deltaPhi[((i + 1) % 2)];

			vec[0] = R*cos(deltaPhiSum);
			vec[1] = R*sin(deltaPhiSum);
			vec[2] = 0;

			use.matrixTimesVec(xRotMat, vec);
			use.matrixTimesVec(zRotMat, vec);

			storagePos[i][0] = vec[0] + pos[0];	
			storagePos[i][1] = vec[1] + pos[1];
			storagePos[i][2] = vec[2] + pos[2];
		}

        std::cout<<"Generating the sequence of coordinates that will be visited DONE"<<std::endl;


		//////////////////////////////////////////////////////
		//		Write sequence to file for controle			//
		//////////////////////////////////////////////////////

        std::cout<<"Write sequence to file for controle START"<<std::endl;
		use.writeCoordToFile("rec3DAbs.txt", storagePos, moves);
        std::cout<<"Write sequence to file for controle DONE"<<std::endl;

		//////////////////////////////////////////
		//		Actual cutting procedure 		//
		//////////////////////////////////////////
        std::cout<<"Actual cutting procedure"<<std::endl;

		//A
        ::gE545.moveTo(storagePos[0][0], storagePos[0][1], storagePos[0][2]);
		std::cout << "was target: "<<storagePos[0][0] << " " << storagePos[0][1] << " " << storagePos[0][2] << std::endl;
        ::gE545.printPosition();
        ::gE545.openShutter();
		//B, C, D, A
		for (int i = 1; i < moves; i++){

			std::cout << "i " << i << std::endl;
            ::gE545.moveTo(storagePos[i][0], storagePos[i][1], storagePos[i][2]);
			std::cout<<"was target: " << storagePos[i][0] << " " << storagePos[i][1] << " " << storagePos[i][2] << std::endl;
            ::gE545.printPosition();

		}
        ::gE545.closeShutter();
        ::gE545.closeShutter();

        ::gE545.setVelocity(9900,9900,9900);
        ::gE545.moveTo(pos[0] + focus[0], pos[1] + focus[1], pos[2] + focus[2]);
        std::cout<<"Actual cutting procedure DONE"<<std::endl;

        std::cout<<"Leaving void figures::rectangle::cutAbs3D()"<<std::endl;
	}
}

