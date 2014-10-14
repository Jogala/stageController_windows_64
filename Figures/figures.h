#ifndef FIGURES_H
#define FIGURES_H

#include "./GlobalVariables.h"
#include "./globalstagecontroller.h"
#include "./Header.h"
#include "./usefulFunctions.h"
#include <Eigen/Core>


namespace figures{

	class figures
	{
	private:

	public:

		//For macros 
        double delayFactor;

	protected:

		usefulFunctions use;
        figures(){
            delayFactor=1;
        }
		~figures(){}
	};

}
#endif
