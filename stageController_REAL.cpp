#include "stageController.h"

void stageController::initialize(){

    if (establishConnection())
    {
        printNameOfConnectedAxis();
        if (switchChannelsOn())
        {
            if (switchAllServosOn())
            {
                if (switchVelocityControlModeOn())
                {
                    if (switchDriftControlModeOn())
                    {
                        setVelocity(50, 50, 50);
                        moveTo(100, 100, 100);
                        setTriggerMode(1, 3);
                        setTriggerMode(2, 3);
                        setTriggerMode(3, 3);
                        setLimits(1, 0, 0);
                        setLimits(2, 0, 0);
                        setLimits(3, 0, 0);
                        std::cout << "E545 ready, press (h)elp for a list of avaliable commands" << std::endl;
                    }
                }
            }
        }
    }


}
bool stageController::establishConnection(){
    ID = PI_ConnectRS232(1, 115200);
    if (ID < 0)
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        printf("ConnectRS232: ERROR %d: %s\n", iError, szErrorMesage);
        return 0;
    }
    else{
        std::cout << "ID = " << ID << " connection established" << std::endl;
        return 1;
    }
}
int stageController::getID(){

    return ID;

}
void stageController::closeConnection(){

    PI_CloseConnection(ID);
    std::cout << "Connection closed" << std::endl;
}
void stageController::printNameOfConnectedAxis(){
    if (!PI_qSAI(ID, szAxes, 16))
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        printf("SAI?: ERROR %d: %s\n", iError, szErrorMesage);
        PI_CloseConnection(ID);
    }
    else
    {
        std::string connectedAxis(szAxes);
        std::cout << "Connected Axis: " << std::endl << connectedAxis << std::endl;
    }

}
bool stageController::switchChannelsOn(){
    int iChnl[3];
    int iVal[3];

    // select the desired piezo channels to change.
    iChnl[0] = 1;
    iChnl[1] = 2;
    iChnl[2] = 3;

    // select the corresponding online mode (1 = online, 0 = offline).
    iVal[0] = 1;
    iVal[1] = 1;
    iVal[2] = 1;

    // Call the ONLine mode command
    if (!PI_ONL(ID, iChnl, iVal, 3/*number of piezo channel to change (array size)*/))
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        printf("ONL: ERROR %d: %s\n", iError, szErrorMesage);
        PI_CloseConnection(ID);
        return 0;
    }
    else
    {
        std::cout << "All channels online" << std::endl;
        return 1;
    }
}

void stageController::setFocus_and_writeValuesToFile(double xFocus, double yFocus, double zFocus){

//    itsXFocus = xFocus;
//    itsYFocus = yFocus;
//    itsZFocus = zFocus;

//    fstream f;
//    f << fixed;
//    f << setprecision(5);
//    f.open(fileName_FocusValues, fstream::out | fstream::trunc);
//    f.close();
//    f.open(fileName_FocusValues, fstream::out | fstream::app);
	
//    f << xFocus << endl;
//    f << yFocus << endl;
//    f << zFocus << endl;
	
//    f.close();
}
void stageController::loadFocusValuesFromFile(){


//    cout << "Old Values Focus" << endl;
//    fstream myReadFile;
//    myReadFile.open(fileName_FocusValues);

//    int i = 0;
//    if (myReadFile.is_open()) {
		

//                    if(!(myReadFile >> itsXFocus)){
//                    itsXFocus=0;
//                    cout<<fileName_FocusValues<<" did not contain values for focus set"<<endl;
//                    cout<<"itsXFocus set to 0"<<endl;
//                    }
//                    cout << itsXFocus << endl;
    
//                    if(!(myReadFile >> itsYFocus)){
//                    itsYFocus=0;
//                    cout<<fileName_FocusValues<<" did not contain values for focus set"<<endl;
//                    cout<<"itsYFocus set to 0"<<endl;
//                    }
//                    cout << itsYFocus << endl;
                    
//                    if(!(myReadFile >> itsZFocus)){
//                    itsZFocus=0;
//                    cout<<fileName_FocusValues<<" did not contain values for focus set"<<endl;
//                    cout<<"itsXFocus set to 0"<<endl;
//                    }
//                    cout << itsZFocus << endl;

				
//                myReadFile.close();
//    }
//    else{
//        cout << "ERROR:" << endl;
//        cout << "void stageController::loadFocusValuesFromFile()" << endl;
//        cout << "Could not load Old Values Focus" << endl;

//        itsXFocus = 0;
//        itsYFocus = 0;
//        itsZFocus = 0;

//        cout << "Focus Values Set to: 0 0 0" << endl;
//    }

	



}
void stageController::moveInFocus(){

    setVelocity(5000, 5000, 5000);
    move(itsXFocus, itsYFocus, itsZFocus);

}

//////////////////////////////////////////////////////
//					Move							//
//////////////////////////////////////////////////////
bool stageController::switchAllServosOn(){

    // Switch on the Servo for all axes
    BOOL servosStatus[3];
    servosStatus[0] = 1; // servo on for first axis in the string 'axes'.
    servosStatus[1] = 1; // servo on for second axis in the string 'axes'.
    servosStatus[2] = 1; // servo on for third axis in the string 'axes'.

    // call the SerVO mode command.
    if (!PI_SVO(ID, szAxes, servosStatus))
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        printf("SVO: ERROR %d: %s\n", iError, szErrorMesage);
        PI_CloseConnection(ID);

        return 0;
    }
    else
    {
        std::cout << "All servos online" << std::endl;
        return 1;
    }


}
void stageController::moveTo(double xCoord, double yCoord, double zCoord){

    double coord[3];
    // move all axes the corresponding position in 'Position'
    coord[0] = xCoord;
    coord[1] = yCoord;
    coord[2] = zCoord;

    if ((0 <= xCoord) && (xCoord <= 200) &&
        (0 <= yCoord) && (yCoord <= 200) &&
        (0 <= zCoord) && (zCoord <= 200))
    {

        // call the MOV command (for closed servo loop).
        if (PI_MOV(ID, szAxes, coord))
        {
            waitUntilMoveFinished();
        }
        else
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            printf("MOV: ERROR %d: %s\n", iError, szErrorMesage);
            PI_CloseConnection(ID);
        }
    }
    else
    {
        std::cout << "void stageController::moveTo(const double coord[3]) says: Out of limits" << std::endl;
    }
}

void stageController::moveTo(const double coord[3]){

    if ((0 <= coord[0]) && (coord[0] <= 200) &&
        (0 <= coord[1]) && (coord[1] <= 200) &&
        (0 <= coord[2]) && (coord[2] <= 200))
    {

        // call the MOV command (for closed servo loop).
        if (PI_MOV(ID, szAxes, coord))
        {
            waitUntilMoveFinished();
        }
        else
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            printf("MOV: ERROR %d: %s\n", iError, szErrorMesage);
            PI_CloseConnection(ID);
        }
    }
    else
    {
        std::cout << "void stageController::moveTo(const double coord[3]) says: Out of limits" << std::endl;
    }
}
void stageController::move(double xDelta, double yDelta, double zDelta){

    double deltaArray[3];
    deltaArray[0] = xDelta;
    deltaArray[1] = yDelta;
    deltaArray[2] = zDelta;

    double position[3];
    getPositon(position);

    position[0] = position[0] + deltaArray[0];
    position[1] = position[1] + deltaArray[1];
    position[2] = position[2] + deltaArray[2];

    if ((0 <= position[0]) && (position[0] <= 200) &&
        (0 <= position[1]) && (position[1] <= 200) &&
        (0 <= position[2]) && (position[2] <= 200))
    {

        if (PI_MVR(ID, szAxes, deltaArray))
        {
            waitUntilMoveFinished();
        }
        else
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            printf("MOV: ERROR %d: %s\n", iError, szErrorMesage);
            PI_CloseConnection(ID);
        }
    }
    else
    {
        std::cout << "void stageController::move(double xDelta, double yDelta, double zDelta) says: Out of limits" << std::endl;
    }
}
void stageController::move(double vec[3]){

    double position[3];
    getPositon(position);

    position[0] = position[0] + vec[0];
    position[1] = position[1] + vec[1];
    position[2] = position[2] + vec[2];

    if ((0 <= position[0]) && (position[0] <= 200) &&
        (0 <= position[1]) && (position[1] <= 200) &&
        (0 <= position[2]) && (position[2] <= 200))
    {

        if (PI_MVR(ID, szAxes, vec))
        {
            waitUntilMoveFinished();
        }
        else
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            printf("MOV: ERROR %d: %s\n", iError, szErrorMesage);
            PI_CloseConnection(ID);
        }
    }
    else
    {
        std::cout << "void stageController::move(double xDelta, double yDelta, double zDelta) says: Out of limits" << std::endl;
    }
}
void stageController::waitUntilMoveFinished(){
    BOOL bIsMoving[3];
    bIsMoving[0] = TRUE;
    bIsMoving[1] = TRUE;
    bIsMoving[2] = TRUE;
    int i = 0;
    while ((bIsMoving[0] == TRUE) || (bIsMoving[1] == TRUE) || (bIsMoving[2] == TRUE))
    {
        ////////////////////////////////////////
        // Read the moving state of the axes. //
        ////////////////////////////////////////

        // if 'axes' = NULL or 'axis' is empty a general moving state of all axes ist returnd in 'bIsMoving[0]'
        // if 'bIsMoving[0]' = TRUE at least one axis of the controller ist still moving.
        // if 'bIsMoving[0]' = FALSE no axis of the contrller is moving.

        // if 'axes != NULL and 'axis' is not empty the moving state of every axis in 'axes' is returned in
        // the arry bIsMoving.
        if (!PI_IsMoving(ID, szAxes, bIsMoving))
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            printf("IsMoving: ERROR %d: %s\n", iError, szErrorMesage);
            PI_CloseConnection(ID);
        }

        /*if (!(i % 200)){
            cout << "bIsMoving[0] " << bIsMoving[0] << endl;
            cout << "bIsMoving[1] " << bIsMoving[1] << endl;
            cout << "bIsMoving[2] " << bIsMoving[2] << endl;
        }*/
        i++;
    }
};
void stageController::printPosition(){

    double position[3];
    if (!PI_qPOS(ID, szAxes, position))
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        printf("POS?: ERROR %d: %s\n", iError, szErrorMesage);
        PI_CloseConnection(ID);
    }
    std::cout << "x : " << position[0] << "\t\t||| y : " << position[1] << "\t\t||| z : " << position[2] << std::endl;

}
void stageController::getPositon(double position[3]){

    if (!PI_qPOS(ID, szAxes, position))
    {
        iError = PI_GetError(ID);
        PI_TranslateError(iError, szErrorMesage, 1024);
        printf("POS?: ERROR %d: %s\n", iError, szErrorMesage);
        PI_CloseConnection(ID);
    }
}
void stageController::getPositon(Eigen::Vector3d & position){

    double pos[3];
    getPositon(pos);

    for (int i = 0; i < 3; i++){
        cout << "pos " << i<<" " << pos[i] << endl;
        position[i] = pos[i];

    }
}

//////////////////////////////////////////////////////
//					Velocity						//
//////////////////////////////////////////////////////
bool stageController::switchVelocityControlModeOn(){

    BOOL boolVCO[3];
    boolVCO[0] = 1;
    boolVCO[1] = 1;
    boolVCO[2] = 1;
    if (!PI_VCO(ID, szAxes, boolVCO))
    {
        std::cout << "ERROR occured while trying to turn on velocity control mode" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Velocity control mode ON for all channels" << std::endl;
        return 1;
    }
}
bool stageController::switchDriftControlModeOn(){

    BOOL boolDCO[3];
    boolDCO[0] = 1;
    boolDCO[1] = 1;
    boolDCO[2] = 1;
    if (!PI_DCO(ID, szAxes, boolDCO))
    {
        std::cout << "ERROR occured while trying to turn on drift control mode" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Drift control mode ON for all channels" << std::endl;
        return 1;
    }
}

void stageController::setVelocity(double xVelocity, double yVelocity, double zVelocity){

    double velocity[3];
    velocity[0] = xVelocity;
    velocity[1] = yVelocity;
    velocity[2] = zVelocity;

    PI_VEL(ID, szAxes, velocity);

    if ((0 <= velocity[0]) && (velocity[0] <= veloLimit) && (0 <= velocity[1]) && (velocity[1] <= veloLimit) && (0 <= velocity[2]) && (velocity[2] <= veloLimit))
    {
        PI_VEL(ID, szAxes, velocity);
    }
    else
    {
        std::cout << "The maximum velocity is " << veloLimit << std::endl;
    }



}
void stageController::setVelocity(const double velocity[3]){

	

    if ((0 <= velocity[0]) && (velocity[0] <= veloLimit) && (0 <= velocity[1]) && (velocity[1] <= veloLimit) && (0 <= velocity[2]) && (velocity[2] <= veloLimit))
    {
        PI_VEL(ID, szAxes, velocity);
    }
    else
    {
        std::cout << "The maximum velocity is " << veloLimit << std::endl;
    }


}
void stageController::deltaVelocity(double xDeltaVelocity, double yDeltaVelocity, double zDeltaVelocity){

    //get current velocity values
    double cVelVal[3];
    getVelocity(cVelVal);

    double newVelocity[3];
    newVelocity[0] = xDeltaVelocity + cVelVal[0];
    newVelocity[1] = yDeltaVelocity + cVelVal[1];
    newVelocity[2] = zDeltaVelocity + cVelVal[2];

	
        setVelocity(newVelocity);
	
}

void stageController::getVelocity(double &xVelocity, double &yVelocity, double &zVelocity){

    double velocityArray[3];

    PI_qVEL(ID, szAxes, velocityArray);

    xVelocity = velocityArray[0];
    yVelocity = velocityArray[1];
    zVelocity = velocityArray[2];

}
void stageController::getVelocity(double velocity[3]){

    PI_qVEL(ID, szAxes, velocity);

}

void stageController::printVelocity(){

    double velocity[3];
    getVelocity(velocity);
    std::cout << "x-Vel : " << velocity[0] << "\t\t||| y-Vel : " << velocity[1] << "\t\t||| z-Vel : " << velocity[2] << std::endl;
}

//////////////////////////////////////////////////////
//				Trigger Digital Output				//
//////////////////////////////////////////////////////
void stageController::setLimits(int whichAxis, double value1, double value2){

    double minNeu;
    double maxNeu;

    double minAlt;
    double maxAlt;

    bool success1 = 0;
    bool success2 = 0;

    int axisAr[1];
    axisAr[0] = whichAxis;
    int triggerParAr[1];
    double valueAr[1];
	
	
    //Wechsle Trigger Mode
    setTriggerMode(whichAxis, 4);

        //Make sure values are in range
        if (!useful.qValuesInLimits(value1, value2))
        {
            std::cout << "ERROR:" << std::endl;
            std::cout << "void stageController::setLimits(int whichAxis, double value1, double value2) says:\n No valid limit values" << std::endl;
        }
        else
        {

            if (value1 <= value2){
                minNeu = value1;
                maxNeu = value2;
            }
            else
            {
                minNeu = value2;
                maxNeu = value1;
            }

			
            getLimits(whichAxis, minAlt, maxAlt);
			
            if (minNeu >= maxAlt){
                //Zuerst maxAlt -> maxNeu
                triggerParAr[0] = 6;
                valueAr[0] = maxNeu;
                success1 = PI_CTO(ID, axisAr, triggerParAr, valueAr, 1);
                //cout << "axis " << whichAxis << " maxAlt -> maxNeu " <<success << endl;

                //Dann minAlt -> minNeu
                triggerParAr[0] = 5;
                valueAr[0] = minNeu;
                success2 = PI_CTO(ID, axisAr, triggerParAr, valueAr, 1);
                //cout << "axis " << whichAxis << " minAlt -> minNeu " << success << endl;
				
            }
            else{

                //Zuerst minAlt -> minNeu
                triggerParAr[0] = 5;
                valueAr[0] = minNeu;
                success1 = PI_CTO(ID, axisAr, triggerParAr, valueAr, 1);
                //cout << "axis " << whichAxis << " minAlt -> minNeu " << success << endl;

                //Dann maxAlt -> maxNeu
                triggerParAr[0] = 6;
                valueAr[0] = maxNeu;
                success2 = PI_CTO(ID, axisAr, triggerParAr, valueAr, 1);
                //cout << "axis " << whichAxis << " maxAlt -> maxNeu " << success << endl;
            }

            if (!success1 || !success2){
                std::cout << "ERROR:" << std::endl;
                std::cout << "PI_CTO(ID, axisAr, triggerParAr, valueAr, 1) in /n void stageController::setLimits(int whichAxis, double value1, double value2) /n returned 0 " << endl;
            }

        }
	
        //Wechsle Trigger Mode
        setTriggerMode(whichAxis, 3);

}

void stageController::setLimitsMin(int whichAxis, double min){

    int piTriggerParameterArray[1];
    int piTriggerOutputIdsArray[1];
    double pdValueArray[1];
    bool tryAgain = 1;

    if (useful.qValueInLimits(min))
    {

        while (tryAgain == 1){

            piTriggerOutputIdsArray[0] = whichAxis;
            piTriggerParameterArray[0] = 5;
            pdValueArray[0] = min;

            tryAgain = !PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
            std::cout << !tryAgain << std::endl;
	
        }//while
    }
    else{
        std::cout << "no valid limit values" << std::endl;
    }

}
void stageController::setLimitsMax(int whichAxis, double max){

    int piTriggerParameterArray[1];
    int piTriggerOutputIdsArray[1];
    double pdValueArray[1];
    bool tryAgain = 1;

    if (useful.qValueInLimits(max))
    {

        while (tryAgain == 1){

            piTriggerOutputIdsArray[0] = whichAxis;
            piTriggerParameterArray[0] = 6;
            pdValueArray[0] = max;

            tryAgain = !PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
            std::cout << !tryAgain << std::endl;

        }//while
    }
    else{
        std::cout << "no valid limit values" << std::endl;
    }

}



void stageController::setTriggerMode(int whichAxis, int mode){

    int piTriggerParameterArray[1];
    int piTriggerOutputIdsArray[1];
    double pdValueArray[1];

    piTriggerOutputIdsArray[0] = whichAxis;
    piTriggerParameterArray[0] = 3;
    pdValueArray[0] = mode;
    std::cout << PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1) << std::endl;

}
void stageController::openShutter(){
    setLimits(1, 0, 200);
    cout << "open Shutter" << endl;
}
void stageController::closeShutter(){
    setLimits(1, 0, 0);
    setLimits(2, 0, 0);
    setLimits(3, 0, 0);
    cout << "close Shutter" << endl;
}

void stageController::getLimits(int whichAxis, double &min, double &max){
    int piTriggerParameterArray[1];
    int piTriggerOutputIdsArray[1];
    double pdValueArray[1];

    piTriggerOutputIdsArray[0] = whichAxis;
    piTriggerParameterArray[0] = 5;
    PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
    min = pdValueArray[0];

    piTriggerOutputIdsArray[0] = whichAxis;
    piTriggerParameterArray[0] = 6;
    PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
    max = pdValueArray[0];
}

void stageController::getLimits(double &xMin, double &xMax, double &yMin, double &yMax, double &zMin, double &zMax){
    int piTriggerParameterArray[1];
    int piTriggerOutputIdsArray[1];
    double pdValueArray[1];

    //x Limits
    piTriggerOutputIdsArray[0] = 1;
    piTriggerParameterArray[0] = 5;
    PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
    xMin = pdValueArray[0];

    piTriggerParameterArray[0] = 6;
    PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
    xMax = pdValueArray[0];

    //y Limits
    piTriggerOutputIdsArray[0] = 2;
    piTriggerParameterArray[0] = 5;
    PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
    yMin = pdValueArray[0];

    piTriggerParameterArray[0] = 6;
    PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
    yMax = pdValueArray[0];

    //z Limits
    piTriggerOutputIdsArray[0] = 3;
    piTriggerParameterArray[0] = 5;
    PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
    zMin = pdValueArray[0];

    piTriggerParameterArray[0] = 6;
    PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
    zMax = pdValueArray[0];
}
void stageController::printLimits(){

    double xMin, xMax, yMin, yMax, zMin, zMax;
    getLimits(1, xMin, xMax);
    getLimits(2, yMin, yMax);
    getLimits(3, zMin, zMax);
    std::cout << xMin << " < x < " << xMax << std::endl << yMin << " < y < " << yMax << std::endl << zMin << " < z < " << zMax << std::endl;
}

bool stageController::checkIfAnyLimit(){
    double xMin, xMax, yMin, yMax, zMin, zMax;
    double pos[3];
    getLimits(xMin, xMax, yMin, yMax, zMin, zMax);
    getPositon(pos);
    if (((xMin <= pos[0]) && (pos[0] <= xMax)) || ((yMin <= pos[1]) && (pos[1] <= yMax)) || ((zMin <= pos[2]) && (pos[2] <= zMax)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//MACRO
void stageController::sendMacros(string nameOfFile){

//    stringstream ss;
//    fstream f;
//    f.open(nameOfFile);

//    if (f.is_open()) {

//        ss << f.rdbuf();
		
//    }
//    f.close();
	
//    string temp = ss.str();
//    PI_GcsCommandset(ID, temp.c_str());
}
void stageController::startMacro(string nameOfmacro){

    cout << "START MACRO" << endl;
    string command = "MAC START " + nameOfmacro;
    PI_GcsCommandset(ID, command.c_str());

}
void stageController::startMacroAndWaitWhileRunning(string nameOfmacro){

    cout << "START MACRO" << endl;

    string command = "MAC START " + nameOfmacro;
    PI_GcsCommandset(ID, command.c_str());

    BOOL macroRunning[1];
    macroRunning[0] = 1;

    sleep(1000);
    int i = 1;
    bool ok = 1;
    while (macroRunning[0]&&ok){
        ok = PI_IsRunningMacro(ID, macroRunning);
        cout << "macroRunning  "<<i<< endl;
        sleep(100);
        i++;
    }

    cout << "MACRO EXECUTION FINISEHD" << endl;
}
string stageController::setLimitsMacro(int whichAxis, double value1, double value2, double altValue1, double altValue2){


    double minNeu;
    double maxNeu;

    double minAlt;
    double maxAlt;

    int axisAr[1];
    axisAr[0] = whichAxis;
    int triggerParAr[1];
    double valueAr[1];

    stringstream f;

    if (altValue1 <= altValue2){
        minAlt = altValue1;
        maxAlt = altValue2;
    }
    else
    {
        minAlt = altValue2;
        maxAlt = altValue1;
    }


    //Make sure values are in range
    if (!useful.qValuesInLimits(value1, value2))
    {
        std::cout << "ERROR:" << std::endl;
        std::cout << "void stageController::setLimits(int whichAxis, double value1, double value2) says:\n No valid limit values" << std::endl;
    }
    else
    {

        if (value1 <= value2){
            minNeu = value1;
            maxNeu = value2;
        }
        else
        {
            minNeu = value2;
            maxNeu = value1;
        }

        f << "CTO " << whichAxis << " 3 4 " << endl;

        if (minNeu >= maxAlt){

            //Zuerst maxAlt -> maxNeu
            f << "CTO " << whichAxis << " 6 " << maxNeu << endl;
            //cout << "axis " << whichAxis << " maxAlt -> maxNeu " <<success << endl;

            //Dann minAlt -> minNeu
            f << "CTO " << whichAxis << " 5 " << minNeu << endl;
            //cout << "axis " << whichAxis << " minAlt -> minNeu " << success << endl;

        }
        else{

            //Zuerst minAlt -> minNeu
            f << "CTO " << whichAxis << " 5 " << minNeu << endl;
            //cout << "axis " << whichAxis << " minAlt -> minNeu " << success << endl;

            //Dann maxAlt -> maxNeu
            f << "CTO " << whichAxis << " 6 " << maxNeu << endl;
            //cout << "axis " << whichAxis << " maxAlt -> maxNeu " << success << endl;
        }

        f << "CTO " << whichAxis << " 3 3 " << endl;

        return f.str();

    }

}

//////////////////////////////////////////////////////
//				Constructros						//
//////////////////////////////////////////////////////
stageController::stageController()
{
    veloLimit=9900;
    loadFocusValuesFromFile();
}
stageController::~stageController()
{

}
