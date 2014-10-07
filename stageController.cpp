#include "stageController.h"
#include <QThread>

int stageController::initialize(){

    std::cout<<"void stageController::initialize() ENTERING"<<std::endl;

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

                            return 1;
                        }
                    }
                }
            }
        }else
        {
            std::cout<<"could not connect to E545 via RS232"<<endl;
            return 0;
        }
   std::cout<<"void stageController::initialize() LEAVING "<<std::endl;


}
bool stageController::establishConnection()
{

    std::cout<<"bool stageController::establishConnection() ENTERING"<<std::endl;

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


    std::cout<<"bool stageController::establishConnection() START"<<std::endl;

}
int stageController::getID(){

    std::cout<<"int stageController::getID()ENTERING"<<std::endl;

    return ID;

    std::cout<<"int stageController::getID()START"<<std::endl;

}
void stageController::closeConnection(){

    std::cout<<"void stageController::closeConnection() ENTERING"<<std::endl;

        PI_CloseConnection(ID);

    std::cout<<"void stageController::closeConnection() LEAVING"<<std::endl;
}
void stageController::printNameOfConnectedAxis(){

    std::cout<<"void stageController::printNameOfConnectedAxis()ENTERING"<<std::endl;

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

    std::cout<<"void stageController::printNameOfConnectedAxis()LEAVING"<<std::endl;

}
bool stageController::switchChannelsOn(){

    std::cout<<"bool stageController::switchChannelsOn() ENTERING"<<std::endl;

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
    std::cout<<"bool stageController::switchChannelsOn() LEAVING"<<std::endl;

}
void stageController::setFocus_and_writeValuesToFile(double focus[3]){

    std::cout<<"void stageController::setFocus_and_writeValuesToFile(double xFocus, double yFocus, double zFocus) ENTERING"<<std::endl;

    for(int i=0;i<3;i++)
    {
        itsFocusValues[i]=focus[i];
    }
    std::cout<<"new focus values assinged to stageController Object"<<std::endl;

    std::fstream f;
    f << std::fixed;
    f << std::setprecision(5);

    std::cout<<"Trying to write new focus values to file "<<fileName_FocusValues<<std::endl;
    f.open(fileName_FocusValues, std::fstream::out | std::fstream::trunc);
    f.close();
    f.open(fileName_FocusValues, std::fstream::out | std::fstream::app);

    if(!(f.is_open()))
    {

        std::cout<<"failed to open "<< fileName_FocusValues <<std::endl;
    }
    else
    {
        std::cout << fileName_FocusValues <<" opened successfully "<<std::endl;

        for(int i=0;i<3;i++)
        {
            f<<itsFocusValues[i]<<std::endl;
        }

        f.close();
        std::cout << fileName_FocusValues <<" closed "<<std::endl;
    }

    focusValuesWereSet=true;

    std::cout<<"void stageController::setFocus_and_writeValuesToFile(double xFocus, double yFocus, double zFocus) LEAVING"<<std::endl;
}

void stageController::loadFocusValuesFromFile(){

    std::cout<<"void stageController::loadFocusValuesFromFile() ENTERING"<<std::endl;

    std::fstream f;

    f.open(fileName_FocusValues);
    if(!(f.is_open()))
    {
        std::cout<<f.is_open()<<std::endl;
        std::cout<<"trying to open"<< fileName_FocusValues << " failed" <<std::endl;
    }else
    {
        std::cout<< fileName_FocusValues << " opened " <<std::endl;

         for(int i = 0; i < 3; i++)
        {
            f>>itsFocusValues[i];
        }

        f.close();
    }

    focusValuesWereSet=true;

    std::cout<<"void stageController::loadFocusValuesFromFile() LEAVING"<<std::endl;
}
void stageController::getFocusValues(double focus[3]){

    std::cout<<"void stageController::getFocusValues(double focus[3]) ENTERING"<<std::endl;


    if(focusValuesWereSet)
    {
        for(int i = 0; i < 3; i++)
        {

            focus[i]=itsFocusValues[i];
        }

    }else{

        std::cout<<"YOU ARE TRYING TO GET FOCUS VALUES BUT THEY HAVE NOT BEEN LOADED YET"<<std::endl;
        std::cout<<"CALL loadFocusValuesFromFile BEFORE USING getFocusValues"<<std::endl;
        std::cout<<"HENCE THE DEFAULT VALUES WHICH ARE SET IN THE CONSTRUCTOR 0 0 0 ARE USED"<<std::endl;
    }

    std::cout<<"void stageController::getFocusValues(double focus[3]) LEAVING"<<std::endl;

}
void stageController::moveInFocus(){


    std::cout<<"void stageController::moveInFocus() ENTERING"<<std::endl;

        setVelocity(5000, 5000, 5000);
        move(itsFocusValues);

    std::cout<<"void stageController::moveInFocus() LEAVING"<<std::endl;

}

void stageController::loadLaserPosValuesFromFile()
{
    std::cout<<"void stageController::loadLaserPosValuesFromFile() ENTERING"<<std::endl;

    std::string fileName = "./Stored_Values/positionLaser.txt";
    std::fstream f;
    f.open(fileName, std::fstream::in);
    f>>itsLaserPosX;
    f>>itsLaserPosY;
    f.close();

    std::cout<<itsLaserPosX<<"\t"<<itsLaserPosY<<std::endl;
    std::cout<<"void stageController::loadLaserPosValuesFromFile() LEAVING"<<std::endl;
}

void stageController::writeLaserPosValuesToFile()
{
    std::cout<<"void stageController::writeLaserPosValuesToFile() ENTERING"<<std::endl;

    std::string fileName = "./Stored_Values/positionLaser.txt";
    std::fstream f;
    f.open(fileName, std::fstream::out | std::fstream::trunc);
    f<<itsLaserPosX<<std::endl;
    f<<itsLaserPosY<<std::endl;
    f.close();

    std::cout<<itsLaserPosX<<"\t"<<itsLaserPosY<<std::endl;
    std::cout<<"void stageController::writeLaserPosValuesToFile()LEAVING"<<std::endl;
}

//////////////////////////////////////////////////////
//					Move							//
//////////////////////////////////////////////////////
bool stageController::switchAllServosOn(){

    std::cout<<"bool stageController::switchAllServosOn() ENTERING"<<std::endl;

        // Switch on the Servo for all axes
        BOOL servosStatus[3];
        servosStatus[0] = 1; // servo on for first axis in the std::string 'axes'.
        servosStatus[1] = 1; // servo on for second axis in the std::string 'axes'.
        servosStatus[2] = 1; // servo on for third axis in the std::string 'axes'.

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
    std::cout<<"bool stageController::switchAllServosOn() LEAVING"<<std::endl;


}
void stageController::moveTo(double xCoord, double yCoord, double zCoord){

    std::cout<<"void stageController::moveTo(double xCoord, double yCoord, double zCoord) ENTERING"<<std::endl;

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
    std::cout<<"void stageController::moveTo(double xCoord, double yCoord, double zCoord) LEAVING"<<std::endl;

}
void stageController::moveTo(const double coord[3]){

    std::cout<<"void stageController::moveTo(const double coord[3]) ENTERING"<<std::endl;

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

    std::cout<<"void stageController::moveTo(const double coord[3]) LEAVING"<<std::endl;

}
void stageController::move(double xDelta, double yDelta, double zDelta){

    std::cout<<"void stageController::move(double xDelta, double yDelta, double zDelta) ENTERING"<<std::endl;


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

        std::cout<<"void stageController::move(double xDelta, double yDelta, double zDelta) LEAVING"<<std::endl;

}
void stageController::move(double vec[3]){


    std::cout<<"void stageController::move(double vec[3])"<<std::endl;

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

    std::cout<<"void stageController::waitUntilMoveFinished() ENTERING"<<std::endl;

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
                std::cout << "bIsMoving[0] " << bIsMoving[0] << std::endl;
                std::cout << "bIsMoving[1] " << bIsMoving[1] << std::endl;
                std::cout << "bIsMoving[2] " << bIsMoving[2] << std::endl;
            }*/
            i++;
        }

    std::cout<<"void stageController::waitUntilMoveFinished() LEAVING"<<std::endl;

}
void stageController::printPosition(){

    std::cout<<"void stageController::printPosition() ENTERING"<<std::endl;

        double position[3];
        if (!PI_qPOS(ID, szAxes, position))
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            printf("POS?: ERROR %d: %s\n", iError, szErrorMesage);
            PI_CloseConnection(ID);
        }
        std::cout << "x : " << position[0] << "\t\t||| y : " << position[1] << "\t\t||| z : " << position[2] << std::endl;

        std::cout<<"void stageController::printPosition() LEAVING"<<std::endl;

}
void stageController::getPositon(double position[3]){

    std::cout<<"void stageController::getPositon(double position[3]) ENTERING"<<std::endl;

        if (!PI_qPOS(ID, szAxes, position))
        {
            iError = PI_GetError(ID);
            PI_TranslateError(iError, szErrorMesage, 1024);
            printf("POS?: ERROR %d: %s\n", iError, szErrorMesage);
            PI_CloseConnection(ID);
        }
    std::cout<<"void stageController::getPositon(double position[3]) LEAVING"<<std::endl;

}
void stageController::getPositon(Eigen::Vector3d & position){

    std::cout<<"void stageController::getPositon(Eigen::Vector3d & position) ENTERING"<<std::endl;

        double pos[3];
        getPositon(pos);

        for (int i = 0; i < 3; i++)
        {
            std::cout << "pos " << i<<" " << pos[i] << std::endl;
            position[i] = pos[i];

        }
    std::cout<<"void stageController::getPositon(Eigen::Vector3d & position) LEAVING"<<std::endl;

}

//////////////////////////////////////////////////////
//					Velocity						//
//////////////////////////////////////////////////////
bool stageController::switchVelocityControlModeOn(){

    std::cout<<"bool stageController::switchVelocityControlModeOn() ENTERING"<<std::endl;

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

    std::cout<<"bool stageController::switchVelocityControlModeOn() LEAVING"<<std::endl;
}
bool stageController::switchDriftControlModeOn(){


    std::cout<<"bool stageController::switchDriftControlModeOn() ENTERING"<<std::endl;


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

    std::cout<<"bool stageController::switchDriftControlModeOn() LEAVING"<<std::endl;
}

void stageController::setVelocity(double xVelocity, double yVelocity, double zVelocity){

    std::cout<<"void stageController::setVelocity(double xVelocity, double yVelocity, double zVelocity) ENTERING"<<std::endl;

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

    std::cout<<"void stageController::setVelocity(double xVelocity, double yVelocity, double zVelocity) LEAVING"<<std::endl;


}
void stageController::setVelocity(const double velocity[3]){

    std::cout<<"void stageController::setVelocity(const double velocity[3]) ENTERING"<<std::endl;

        if ((0 <= velocity[0]) && (velocity[0] <= veloLimit) && (0 <= velocity[1]) && (velocity[1] <= veloLimit) && (0 <= velocity[2]) && (velocity[2] <= veloLimit))
        {
            PI_VEL(ID, szAxes, velocity);
        }
        else
        {
            std::cout << "The maximum velocity is " << veloLimit << std::endl;
        }

    std::cout<<"void stageController::setVelocity(const double velocity[3]) LEAVING"<<std::endl;

}
void stageController::deltaVelocity(double xDeltaVelocity, double yDeltaVelocity, double zDeltaVelocity){

    std::cout<<"void stageController::deltaVelocity(double xDeltaVelocity, double yDeltaVelocity, double zDeltaVelocity) ENTERING"<<std::endl;

        //get current velocity values
        double cVelVal[3];
        getVelocity(cVelVal);

        double newVelocity[3];
        newVelocity[0] = xDeltaVelocity + cVelVal[0];
        newVelocity[1] = yDeltaVelocity + cVelVal[1];
        newVelocity[2] = zDeltaVelocity + cVelVal[2];


        setVelocity(newVelocity);

        std::cout<<"void stageController::deltaVelocity(double xDeltaVelocity, double yDeltaVelocity, double zDeltaVelocity) LEAVING"<<std::endl;

}

void stageController::getVelocity(double &xVelocity, double &yVelocity, double &zVelocity){


    std::cout<<"void stageController::getVelocity(double &xVelocity, double &yVelocity, double &zVelocity) ENTERING"<<std::endl;


        double velocityArray[3];

        PI_qVEL(ID, szAxes, velocityArray);

        xVelocity = velocityArray[0];
        yVelocity = velocityArray[1];
        zVelocity = velocityArray[2];

    std::cout<<"void stageController::getVelocity(double &xVelocity, double &yVelocity, double &zVelocity) LEAVING"<<std::endl;

}
void stageController::getVelocity(double velocity[3]){

    std::cout<<"void stageController::getVelocity(double velocity[3]) ENTERING"<<std::endl;


        PI_qVEL(ID, szAxes, velocity);

    std::cout<<"void stageController::getVelocity(double velocity[3]) ENTERING"<<std::endl;


}

void stageController::printVelocity(){

    std::cout<<"void stageController::printVelocity() ENTERING"<<std::endl;

        double velocity[3];
        getVelocity(velocity);
        std::cout << "x-Vel : " << velocity[0] << "\t\t||| y-Vel : " << velocity[1] << "\t\t||| z-Vel : " << velocity[2] << std::endl;

    std::cout<<"void stageController::printVelocity() LEAVING"<<std::endl;

}

//////////////////////////////////////////////////////
//				Trigger Digital Output				//
//////////////////////////////////////////////////////
void stageController::setLimits(int whichAxis, double value1, double value2){

    std::cout<<"void stageController::setLimits(int whichAxis, double value1, double value2) ENTERING"<<std::endl;

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
                //std::cout << "axis " << whichAxis << " maxAlt -> maxNeu " <<success << std::endl;

                //Dann minAlt -> minNeu
                triggerParAr[0] = 5;
                valueAr[0] = minNeu;
                success2 = PI_CTO(ID, axisAr, triggerParAr, valueAr, 1);
                //std::cout << "axis " << whichAxis << " minAlt -> minNeu " << success << std::endl;

            }
            else{

                //Zuerst minAlt -> minNeu
                triggerParAr[0] = 5;
                valueAr[0] = minNeu;
                success1 = PI_CTO(ID, axisAr, triggerParAr, valueAr, 1);
                //std::cout << "axis " << whichAxis << " minAlt -> minNeu " << success << std::endl;

                //Dann maxAlt -> maxNeu
                triggerParAr[0] = 6;
                valueAr[0] = maxNeu;
                success2 = PI_CTO(ID, axisAr, triggerParAr, valueAr, 1);
                //std::cout << "axis " << whichAxis << " maxAlt -> maxNeu " << success << std::endl;
            }

            if (!success1 || !success2){
                std::cout << "ERROR:" << std::endl;
                std::cout << "PI_CTO(ID, axisAr, triggerParAr, valueAr, 1) in /n void stageController::setLimits(int whichAxis, double value1, double value2) /n returned 0 " << std::endl;
            }

        }

        //Wechsle Trigger Mode
        setTriggerMode(whichAxis, 3);

        std::cout<<"void stageController::setLimits(int whichAxis, double value1, double value2) LEAVING"<<std::endl;

}

void stageController::setLimitsMin(int whichAxis, double minima){


    std::cout<<"void stageController::setLimitsMin(int whichAxis, double minima) ENTERING"<<std::endl;

        int piTriggerParameterArray[1];
        int piTriggerOutputIdsArray[1];
        double pdValueArray[1];
        bool tryAgain = 1;

        if (useful.qValueInLimits(minima))
        {

            while (tryAgain == 1){

                piTriggerOutputIdsArray[0] = whichAxis;
                piTriggerParameterArray[0] = 5;
                pdValueArray[0] = minima;

                tryAgain = !PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
                std::cout << !tryAgain << std::endl;

            }//while
        }
        else{
            std::cout << "no valid limit values" << std::endl;
        }
    std::cout<<"void stageController::setLimitsMin(int whichAxis, double minima) LEAVING"<<std::endl;


}
void stageController::setLimitsMax(int whichAxis, double maxima){

    std::cout<<"void stageController::setLimitsMax(int whichAxis, double maxima) ENTERING"<<std::endl;

        int piTriggerParameterArray[1];
        int piTriggerOutputIdsArray[1];
        double pdValueArray[1];
        bool tryAgain = 1;

        if (useful.qValueInLimits(maxima))
        {

            while (tryAgain == 1){

                piTriggerOutputIdsArray[0] = whichAxis;
                piTriggerParameterArray[0] = 6;
                pdValueArray[0] = maxima;

                tryAgain = !PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
                std::cout << !tryAgain << std::endl;

            }//while
        }
        else{
            std::cout << "no valid limit values" << std::endl;
        }

        std::cout<<"void stageController::setLimitsMax(int whichAxis, double maxima) LEAVING"<<std::endl;

}



void stageController::setTriggerMode(int whichAxis, int mode){

    std::cout<<"void stageController::setTriggerMode(int whichAxis, int mode) ENTERING"<<std::endl;

        int piTriggerParameterArray[1];
        int piTriggerOutputIdsArray[1];
        double pdValueArray[1];

        piTriggerOutputIdsArray[0] = whichAxis;
        piTriggerParameterArray[0] = 3;
        pdValueArray[0] = mode;
        std::cout << PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1) << std::endl;

    std::cout<<"void stageController::setTriggerMode(int whichAxis, int mode) LEAVING"<<std::endl;

}
void stageController::openShutter(){

    std::cout<<"void stageController::openShutter() ENTERING"<<std::endl;

        setLimits(1, 0, 200);
        std::cout << "open Shutter" << std::endl;

    std::cout<<"void stageController::openShutter() LEAVING"<<std::endl;

}
void stageController::closeShutter(){

    std::cout<<"void stageController::closeShutter() ENTERING"<<std::endl;


        setLimits(1, 0, 0);
        setLimits(2, 0, 0);
        setLimits(3, 0, 0);


    std::cout<<"LEAVING void stageController::closeShutter() LEAVING"<<std::endl;
}

void stageController::getLimits(int whichAxis, double &inMin, double &inMax){

    std::cout<<"void stageController::getLimits(int whichAxis, double &inMin, double &inMax) ENTERING"<<std::endl;

        int piTriggerParameterArray[1];
        int piTriggerOutputIdsArray[1];
        double pdValueArray[1];

        piTriggerOutputIdsArray[0] = whichAxis;
        piTriggerParameterArray[0] = 5;
        PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
        inMin = pdValueArray[0];

        piTriggerOutputIdsArray[0] = whichAxis;
        piTriggerParameterArray[0] = 6;
        PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
        inMax = pdValueArray[0];

        std::cout<<"void stageController::getLimits(int whichAxis, double &inMin, double &inMax) LEAVING"<<std::endl;

}

void stageController::getLimits(double &xMin, double &xMax, double &yMin, double &yMax, double &zMin, double &zMax){

    std::cout<<"void stageController::getLimits(double &xMin, double &xMax, double &yMin, double &yMax, double &zMin, double &zMax) ENTERING"<<std::endl;

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

    std::cout<<"void stageController::getLimits(double &xMin, double &xMax, double &yMin, double &yMax, double &zMin, double &zMax) LEAVING"<<std::endl;

}

void stageController::printLimits(){

    std::cout<<"void stageController::printLimits() ENTERING"<<std::endl;

        double xMin, xMax, yMin, yMax, zMin, zMax;
        getLimits(1, xMin, xMax);
        getLimits(2, yMin, yMax);
        getLimits(3, zMin, zMax);
        std::cout << xMin << " < x < " << xMax << std::endl << yMin << " < y < " << yMax << std::endl << zMin << " < z < " << zMax << std::endl;

    std::cout<<"void stageController::printLimits() LEAVING"<<std::endl;
}

bool stageController::checkIfAnyLimit(){

    std::cout<<"bool stageController::checkIfAnyLimit() ENTERING"<<std::endl;

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

        std::cout<<"bool stageController::checkIfAnyLimit() LEAVING"<<std::endl;

}

//MACRO
void stageController::sendMacros(std::string nameOfFile){

    std::cout<<"void stageController::sendMacros(std::string nameOfFile) ENTERING"<<std::endl;


        std::stringstream ss;
        std::fstream f;
        f.open(nameOfFile);

        if (f.is_open()) {

            ss << f.rdbuf();

        }
        f.close();

        std::string temp = ss.str();
        PI_GcsCommandset(ID, temp.c_str());

    std::cout<<"void stageController::sendMacros(std::string nameOfFile) LEAVING"<<std::endl;

}
void stageController::startMacro(std::string nameOfmacro){

    std::cout<<"void stageController::startMacro(std::string nameOfmacro) ENTERING"<<std::endl;


    std::cout << "START MACRO" << std::endl;
    std::string command = "MAC START " + nameOfmacro;
    PI_GcsCommandset(ID, command.c_str());


    std::cout<<"void stageController::startMacro(std::string nameOfmacro) LEAVING"<<std::endl;


}
void stageController::startMacroAndWaitWhileRunning(std::string nameOfmacro){

    std::cout<<"void stageController::startMacroAndWaitWhileRunning(std::string nameOfmacro) ENTERING"<<std::endl;


        std::cout << "START MACRO" << std::endl;

        std::string command = "MAC START " + nameOfmacro;
        PI_GcsCommandset(ID, command.c_str());

        BOOL macroRunning[1];
        macroRunning[0] = 1;

        QThread::msleep(1000);
        int i = 1;
        bool ok = 1;
        while (macroRunning[0]&&ok){
            ok = PI_IsRunningMacro(ID, macroRunning);
            std::cout << "macroRunning  "<<i<< std::endl;
            QThread::msleep(100);
            i++;
        }

        std::cout << "MACRO EXECUTION FINISEHD" << std::endl;

        std::cout<<"void stageController::startMacroAndWaitWhileRunning(std::string nameOfmacro) LEAVING"<<std::endl;

}
std::string stageController::setLimitsMacro(int whichAxis, double value1, double value2, double altValue1, double altValue2){


    std::cout<<"std::string stageController::setLimitsMacro(int whichAxis, double value1, double value2, double altValue1, double altValue2) ENTERING"<<std::endl;

        double minNeu;
        double maxNeu;

        double minAlt;
        double maxAlt;

        int axisAr[1];
        axisAr[0] = whichAxis;

        std::stringstream f;

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

            f << "CTO " << whichAxis << " 3 4 " << std::endl;

            if (minNeu >= maxAlt){

                //Zuerst maxAlt -> maxNeu
                f << "CTO " << whichAxis << " 6 " << maxNeu << std::endl;
                //std::cout << "axis " << whichAxis << " maxAlt -> maxNeu " <<success << std::endl;

                //Dann minAlt -> minNeu
                f << "CTO " << whichAxis << " 5 " << minNeu << std::endl;
                //std::cout << "axis " << whichAxis << " minAlt -> minNeu " << success << std::endl;

            }
            else{

                //Zuerst minAlt -> minNeu
                f << "CTO " << whichAxis << " 5 " << minNeu << std::endl;
                //std::cout << "axis " << whichAxis << " minAlt -> minNeu " << success << std::endl;

                //Dann maxAlt -> maxNeu
                f << "CTO " << whichAxis << " 6 " << maxNeu << std::endl;
                //std::cout << "axis " << whichAxis << " maxAlt -> maxNeu " << success << std::endl;
            }

            f << "CTO " << whichAxis << " 3 3 " << std::endl;

            return f.str();

        }

    std::cout<<"std::string stageController::setLimitsMacro(int whichAxis, double value1, double value2, double altValue1, double altValue2) LEAVING"<<std::endl;

}

//////////////////////////////////////////////////////
//				Constructros						//
//////////////////////////////////////////////////////
stageController::stageController()
{
    std::cout<<"stageController::stageController() ENTERING"<<std::endl;
    fileName_FocusValues = "./Stored_Values/focus.txt";
    veloLimit=9900;

    for(auto item : itsFocusValues)
    {
        item=0;
    }

    loadLaserPosValuesFromFile();



    std::cout<<"stageController::stageController() LEAVING"<<std::endl;
}
stageController::~stageController()
{
}
