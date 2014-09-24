#include "spiral.h"


void    figures::spiral::loadValuesFromTextFile(){

    fstream f;

    f.open(storedValuesPath);

    if (f.is_open()) {

        for(auto item : itsValues){
            f>>item;
        }

    }
    f.close();

}
void    figures::spiral::writeValuesToTextFile(){

   fstream f;
   f.open(storedValuesPath);

   cout<<"writing values to "<<storedValuesPath<<endl;
   for(auto item : itsValues)
   {
       cout<<item<<endl;
       f<<item<<endl;
   }

   f.close();
}

void    figures::spiral::setValue(int i, double value){

    itsValues[i]=value;

}
double  figures::spiral::getValue(int i){

    return itsValues[i];
}

void    figures::spiral::printMemberVariables(){

    int i = 0;
    for(auto item : itsValues){
        cout<<i++<<" "<<item<<endl;
    }

}


void figures::spiral::cutAbsMacroSpiral3D()
{
    //////////////////////////////////////////
    //                 Set up               //
    //////////////////////////////////////////

    double R=itsValues[0];
    double R_end = itsValues[1];
    int    steps=itsValues[2];
    int    sectors=itsValues[3];
    double phi0 = itsValues[4];
    double rotAngleX=itsValues[5];
    double rotAngleZ=itsValues[6];
    double velocity = itsValues[7];

    double deltaR = (R-R_end) / (sectors-1);
	int stepsPerSector = steps / sectors;
	double pos[3];
    ::gE545.getPositon(pos);
    double focus[3];
    ::gE545.getFocusValues(focus);

	double deltaAlpha = (2 * pi) / steps;
	double vec[3];
	auto storPos = vector<vector<double>>(steps + 1, vector<double>(3));
	auto delay = vector<double>(steps + 1);

	string macroName = "macroSpiral";
	string nameFile = "macroSpiral.txt";

    double phi0RotMat[3][3];
	double xRotMat[3][3];
	double zRotMat[3][3];

    use.setZRotMatrix(phi0RotMat,phi0);
    use.setXRotMatrix(xRotMat,rotAngleX);
    use.setZRotMatrix(zRotMat,rotAngleZ);

    //########################################################################################################################################################


	//////////////////////////////////////////
	//		Generating the coordinates		//
	//////////////////////////////////////////
	int n = 0;
	int nOld = n;
	for (int i = 1; i <= steps + 1; i++){

		if ((i - 1) == 0){

			delay[0] = (R / velocity) * 1000;
		
		}
		else{

			if (nOld != n){

				R = R - deltaR;
				delay[(i - 1)] = (deltaR / velocity) * 1000;

			}
			else{

				delay[(i - 1)] = 1000 * (sin(deltaAlpha / 2) * 2 * R*delayFactor) / velocity;

			}
		}

		vec[0] = R*cos(deltaAlpha*(i - 1) + pi / 2);
		vec[1] = R*sin(deltaAlpha*(i - 1) + pi / 2);
		vec[2] = 0;

        use.matrixTimesVec(phi0RotMat, vec);
        use.matrixTimesVec(xRotMat, vec);
        use.matrixTimesVec(zRotMat, vec);

		storPos[(i - 1)][0] = vec[0] + pos[0];
		storPos[(i - 1)][1] = vec[1] + pos[1];
		storPos[(i - 1)][2] = vec[2] + pos[2];

		nOld = n;
		n = i / stepsPerSector;
	
		if (n == sectors){
			n = n - 1;
		}
	}
    //########################################################################################################################################################

    ///////////////////////////////////////
    //Write sequence to file for controle//
    ///////////////////////////////////////

	int color = 1;
	fstream fc;
	fc << fixed;
	fc << setprecision(5);
	fc.open("cutAbsMacroSpiral3D_Coord.txt", fstream::out | fstream::trunc);
	fc.close();
	fc.open("cutAbsMacroSpiral3D_Coord.txt", fstream::out | fstream::app);

    n = 0;
	nOld = 0;
	for (int i = 0; i < steps + 1; i++){
		
		for (int j = 0; j < 3; j++){

			fc << storPos[i][j] << "\t";
		}

		fc << delay[i] << endl;
	
	}
	fc.close();

    //########################################################################################################################################################

	//////////////////////////////////////////
	//		Actual cutting procedure 		//
	//////////////////////////////////////////

	double diff[3];
	for (int i = 0; i < 3; i++){
		diff[i] = storPos[steps][i];
	}


	fstream f;
	f << fixed;
	f << setprecision(5);
	f.open(nameFile, fstream::out | fstream::trunc);
	f.close();
	f.open(nameFile, fstream::out | fstream::app);

	f << "MAC BEG " << macroName << endl;
	f << "VEL A " << velocity << " B " << velocity << " C " << velocity << endl;
	f << "MOV A " << storPos[0][0] << " B " << storPos[0][1] << " C " << storPos[0][2] << endl;
	f << "DEL " << delay[0] << endl;
    f << ::gE545.setLimitsMacro(1, 0, 200, 0, 0);
	
	int shutterCounter=0; 
	for (int i = 1; i < steps + 1; i++){

		if (i>=2){
			if (delay[i] != delay[i - 1]){

				if (!(shutterCounter % 2)){
					//Close Shutter
                    f << ::gE545.setLimitsMacro(1, 0, 0, 0, 200);
				}
				else{
					//Open Shutter
                    f << ::gE545.setLimitsMacro(1, 0, 200, 0, 0);
				}
				shutterCounter = shutterCounter + 1;
			}
		}

			f << "MOV A " << storPos[i][0] << " B " << storPos[i][1] << " C " << storPos[i][2] << endl;
			f << "DEL " << delay[i] << endl;
	}
	//Close Shutter
    f << ::gE545.setLimitsMacro(1, 0, 0, 0, 200);
	f << "VEL A " << "9000" << " B " << "9000" << " C " << "9000" << endl;
    f << "MOV A " << pos[0] + focus[0] << " B " << pos[1] +focus[1] << " C " << pos[2] + focus[2] << endl;
	f << "DEL 1000" << endl;
	f << "MAC END" << endl;
	f.close();

	cout << "Macro written to file:" << nameFile << endl;
	cout << "SENDING MACRO TO CONTROLLER..." << endl;
    ::gE545.sendMacros(nameFile);

    ::gE545.closeShutter();
    ::gE545.startMacroAndWaitWhileRunning(macroName);

    //########################################################################################################################################################
}
