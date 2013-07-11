/**
	Module to run regression for boxcounting.

	Changes a double[3] such that regressionArray[0] = slope,
	regressionArray[1] = R^2, and regressionArray[2] = y-int.

	Implemented in boxCounter3D.cpp:
		Fractal analysis module utilizing boxcounting to determine 
		the fractal dimension of a shape in the input text/binary file.

		Prints to terminal:
			- the results at each level of analysis
			- the overall dimension as determined by least-squares regression
			- an R^2 value
			
		@author Samuel Brenner
		@version July 11, 2013

	@author Samuel Brenner
	@version July 11, 2013

**/

#ifndef REGMOD_h

#define REGMOD_h

void slope(double** arrayIn, int arrayLength, double* regressionArray);


#endif