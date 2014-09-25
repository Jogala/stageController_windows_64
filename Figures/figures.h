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




	//////////////////////////////////////
	//		surface rectangle			//
	//////////////////////////////////////
	class surfaceRectangle : public figures
	{
	private:

		double a, b, phi0, velocity;
		int resolution;
		char orientation;

	public:
		void set(double aIn, double bIn, double phi0In, double velocityIn, int resoluationIn, char longOrShortSide);
		void cutRel();
		void cutAbs();


		surfaceRectangle(){	
		}

		~surfaceRectangle(){}

	};





}
#endif
