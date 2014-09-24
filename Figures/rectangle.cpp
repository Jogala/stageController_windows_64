#include "rectangle.h"


void    figures::rectangle::loadValuesFromTextFile()
{
    fstream f;

    f.open(storedValuesPath);

    if (f.is_open()) {

        for(auto item : itsValues){
            f>>item;
        }

    }
    f.close();

}
void    figures::rectangle::writeValuesToTextFile(){
   cout<<"void    figures::rectangle::writeValuesToTextFile()"<<endl;

   fstream f;
   f.open(storedValuesPath);

   if(!(f.is_open()))
   {
     cout<<"failed to open "<< storedValuesPath <<endl;
   }else
   {

   cout << storedValuesPath <<" opened successfully "<<endl;

   for(auto item : itsValues)
   {
       f<<item<<endl;
   }

   f.close();
   cout << storedValuesPath <<" closed "<<endl;
   }

   cout<<"Leaving void    figures::rectangle::writeValuesToTextFile()"<<endl;
}

void    figures::rectangle::setValue(int i, double value){

    cout<<"void    figures::rectangle::setValue(int i, double value)"<<endl;
    itsValues[i]=value;
    cout<<"itsValue("<<i<<") = "<<itsValues[i]<<endl;

}
double  figures::rectangle::getValue(int i){

    return itsValues[i];
}

void    figures::rectangle::printMemberVariables(){

    int i = 0;
    for(auto item : itsValues){
        cout<<i++<<" "<<item<<endl;
    }

}

void figures::rectangle::cutAbs3D(){
cout<<"void figures::rectangle::cutAbs3D()"<<endl;

cout<<"assign values from array to variables with more concrete names"<<endl;
    double a=itsValues[0];
    double b=itsValues[1];
    double phi0=itsValues[2];
    double rotAngleX=itsValues[3];
    double rotAngleZ=itsValues[4];
    double velocity = itsValues[5];
cout<<"assign values from array to variables with more concrete names DONE"<<endl;

    if ((a <= 0) || (b <= 0))
    {
		cout << "ERROR:" << endl;
		cout << "a <= 0 or b <= 0 are no exaptable values for a rectangle " << endl;
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
        cout<<"Generating the sequence of coordinates that will be visited"<<endl;

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

        cout<<"Generating the sequence of coordinates that will be visited DONE"<<endl;


		//////////////////////////////////////////////////////
		//		Write sequence to file for controle			//
		//////////////////////////////////////////////////////

        cout<<"Write sequence to file for controle"<<endl;
		use.writeCoordToFile("rec3DAbs.txt", storagePos, moves);
        cout<<"Write sequence to file for controle DONE"<<endl;

		//////////////////////////////////////////
		//		Actual cutting procedure 		//
		//////////////////////////////////////////
        cout<<"Actual cutting procedure"<<endl;

		//A
        ::gE545.moveTo(storagePos[0][0], storagePos[0][1], storagePos[0][2]);
		cout << "was target: "<<storagePos[0][0] << " " << storagePos[0][1] << " " << storagePos[0][2] << endl;
        ::gE545.printPosition();
        ::gE545.openShutter();
		//B, C, D, A
		for (int i = 1; i < moves; i++){

			cout << "i " << i << endl;
            ::gE545.moveTo(storagePos[i][0], storagePos[i][1], storagePos[i][2]);
			cout<<"was target: " << storagePos[i][0] << " " << storagePos[i][1] << " " << storagePos[i][2] << endl;
            ::gE545.printPosition();

		}
        ::gE545.closeShutter();
        ::gE545.closeShutter();


        ::gE545.moveTo(pos[0] + focus[0], pos[1] + focus[1], pos[2] + focus[2]);
        cout<<"Actual cutting procedure DONE"<<endl;

        cout<<"Leaving void figures::rectangle::cutAbs3D()"<<endl;
	}
}

