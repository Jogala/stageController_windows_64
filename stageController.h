#ifndef STAGECONTROLLER_H
#define STAGECONTROLLER_H

#include "./Header.h"
#include "./usefulFunctions.h"
#include "./GlobalVariables.h"
#include "./PI_stuff/PI_GCS2_DLL.h"


class stageController
{

private:
    double Position[3];
    usefulFunctions useful;
    std::string fileName_FocusValues;


public:
    //Variables

    int ID;
    char szErrorMesage[1024];
    int	iError;
    char szAxes[17];
    double itsLaserPosX;
    double itsLaserPosY;
    double itsFocusValues[3];
    double itsVeloLimit;


    //Methods

    ///////////////////
    // Initialization//
    ///////////////////
    int initialize();

    bool focusValuesWereSet = false;
    void getFocusValues(double focus[3]);
    void setFocus_and_writeValuesToFile(double focus[3]);
    void loadFocusValuesFromFile();
    void moveInFocus();

    void loadLaserPosValuesFromFile();
    void writeLaserPosValuesToFile();


    int getID();
    void printMemberVariables(){

        std::cout << "ID = " << "\t" << ID << std::endl;

        for(int i = 0; i < 3; i++)
        {
            std::cout << "itsFocusValues["<<i<<"] = " << "\t" << itsFocusValues[i] << std::endl;
        }

    }

    ////////////////////////////////////////////////////////////////////
    // connect to the E-517 over RS-232 (COM port 1, baudrate 38400). //
    ////////////////////////////////////////////////////////////////////
    bool establishConnection();
    //returns 0 in case of success, and 1 for failure

    ////////////////////
    //Close Connection//
    ////////////////////
    void closeConnection();

    /////////////////////////////////////////
    // Get the name of the connected axis. //
    /////////////////////////////////////////
    void printNameOfConnectedAxis();

    /////////////////////////////////////////////////
    //// Switch the piezo channels to online mode. //
    /////////////////////////////////////////////////
    bool switchChannelsOn();


    ///////////////////////////////////////////
    //// close the servo loop (closed-loop). //
    ///////////////////////////////////////////
    bool switchAllServosOn();

    ///////////////////////////////////////////
    //// move to coordinates	(closed-loop)//
    ///////////////////////////////////////////
    //uses waitUntilMoveFinished();
    void moveTo(double xCoord, double yCoord, double zCoord);
    void moveTo(const double coordArray[3]);

    ///////////////////////////////////////////
    //// relative movement   	(closed-loop)//
    ///////////////////////////////////////////
    void move(double xDelta, double yDelta, double zDelta);
    void move(double vec[3]);

    void printPosition();
    void getPositon(double position[3]);
    void getPositon(Eigen::Vector3d & position);

    ///////////////////////////////////////////
    //// set velocity			(closed-loop)//
    ///////////////////////////////////////////
    void setVelocity(double xVelocity, double yVelocity, double zVelocity);
    void setVelocity(const double velocity[3]);
    void getVelocity(double &xVelocity, double &yVelocity, double &zVelocity);
    void getVelocity(double velocity[3]);
    void printVelocity();

    ///////////////////////////////////////////////////////
    //// change velocity by the delta values(closed-loop)//
    ///////////////////////////////////////////////////////
    void deltaVelocity(double xDeltaVelocity, double yDeltaVelocity, double zDeltaVelocity);

    ////////////////////////////////////////////////
    //// Wait until the closed loop move is done. //
    ////////////////////////////////////////////////
    void waitUntilMoveFinished();


    /////////////////////////////////////////////////////////////////////////
    //// Both VCM and DCM have to be activated before using setVelocity	   //
    /////////////////////////////////////////////////////////////////////////
    bool switchVelocityControlModeOn();
    bool switchDriftControlModeOn();

    void setTriggerMode(int axis, int mode);
    void setLimits(int xYorZaxis, double minima, double maxima);
    void setLimitsMin(int whichAxis, double minima);
    void setLimitsMax(int whichAxis, double maxima);

    std::string setLimitsMacro(int whichAxis, double value1, double value2, double altValue1, double altValue2);

    void getLimits(int whichAxis, double &minima, double &maxima);
    void getLimits(double &xMin, double &xMax, double &yMin, double &yMax, double &zMin, double &zMax);
    void printLimits();

    bool checkIfAnyLimit();
    void getConfigOfTriggerOutput();

    //////////////////////////////////////
    //              MACRO               //
    //////////////////////////////////////

    void stopAllMotion();
    void createMacroFromCoordinatesAndCut(std::string pathToCoordinates,std::string nameOfMacro, int velocity, double delayFactor);

    void sendMacro(std::string nameOfFile);
    void startMacroAndWaitWhileRunning(std::string nameOfmacro);
    void startMacro(std::string nameOfmacro);

    void openShutter();
    void closeShutter();

    stageController();
    ~stageController();
};

#endif
