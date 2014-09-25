#include "usefulFunctions.h"

bool usefulFunctions::cinAndCheckForDoubleAndLimits(double & xStepSize){

    double newValue;

    do{
        if (std::cin >> newValue)
        {
            if ((0 <= newValue) && (newValue <= 200)){
                xStepSize = newValue;
                return 1;
            }
            else
            {
                std::cout << "No new value was set; value was out of range [0,200]" << std::endl;
                return 0;
            }
        }
        else
        {
            std::cout << "not a number... try again, escape by typing for example -1" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');

            return 0;
        }
    } while (1);

}

bool usefulFunctions::cinAndCheckForDoubleAndLimits(double & xStepSize, double minima){

    double newValue;

    do{
        if (std::cin >> newValue)
        {
            if ((minima <= newValue)){
                xStepSize = newValue;
                return 1;
            }
            else
            {
                std::cout << "No new value was set; value was out of range [0,200]" << std::endl;
                return 0;
            }
        }
        else
        {
            std::cout << "not a number... try again, escape by typing for example -1" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');

            return 0;
        }
    } while (1);
}

bool usefulFunctions::cinAndCheckForDoubleAndLimits(double & xStepSize, double minima, double maxima){

    double newValue;

    do{
        if (std::cin >> newValue)
        {
            if ((minima <= newValue) && (newValue <= maxima)){
                xStepSize = newValue;
                return 1;
            }
            else
            {
                std::cout << "No new value was set; value was out of range [0,200]" << std::endl;
                return 0;
            }
        }
        else
        {
            std::cout << "not a number... try again, escape by typing for example -1" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');

            return 0;
        }
    } while (1);
}

void usefulFunctions::cinAndCheckForDouble(double & xStepSize){
    bool success = 0;
    double newValue;

    do{
        if (std::cin >> newValue)
        {

            xStepSize = newValue;
            success = 1;
        }
        else
        {
            std::cout << "not a number... try again" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    } while (!success);
}

bool usefulFunctions::qValueInLimits(double value){
    if ((0 <= value) && (value <= 200)){
        return 1;
    }
    else{
        return 0;
    }
}

bool usefulFunctions::qValuesInLimits(double value1, double value2){
    if ((0 <= value1) && (value1 <= 200) && (0 <= value2) && (value2 <= 200)){
        return 1;
    }
    else{
        return 0;
    }
}

usefulFunctions::usefulFunctions()
{
    std::cout<<"usefulFunctions::usefulFunctions() ENTERING"<<std::endl;
    std::cout<<"usefulFunctions::usefulFunctions() LEAVING"<<std::endl;

}

usefulFunctions::~usefulFunctions()
{
}
