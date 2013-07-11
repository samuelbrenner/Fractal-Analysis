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


#include "regressionModule.h"

#include <math.h>

double stdev(double* arrayIn, double arrayMean, int arrayLength);

double corrCoeff(double* arrayX, double* arrayY, double meanX, 
	double meanY, double stdevX, double stdevY, int length);

double mean(double* arrayIn, int arrayLength);

void slope(double** arrayIn, int arrayLength, double* regressionArray){
	
	double* arrayX = new double[3];

	for(int i = 0; i < 3; i++){
		arrayX[i] = arrayIn[i][0];
	}

	double* arrayY = new double[3];
	for(int i = 0; i < 3; i++){
		arrayY[i] = arrayIn[i][1];
	}

	double meanX = mean(arrayX, 3);
	double meanY = mean(arrayY, 3);

	double stdevX = stdev(arrayX, meanX, 3);
	double stdevY = stdev(arrayY, meanY, 3);

	double r = corrCoeff(arrayX, arrayY, meanX, meanY, stdevX, stdevY, 3);

	double slope = r 
		* stdevY / stdevX;


	delete[] arrayX;
 	delete[] arrayY;

 	regressionArray[0] = slope;
 	regressionArray[1] = pow(r, 2);
 	regressionArray[2] = meanY - slope * meanX;
}

double stdev(double* arrayIn, double arrayMean, int arrayLength){

	double squaresSum = 0;

	for(int i = 0; i < arrayLength; i++){
		squaresSum += pow(arrayIn[i] - arrayMean, 2);
	}

	return sqrt(squaresSum / (arrayLength - 1));
}

double corrCoeff(double* arrayX, double* arrayY, double meanX, 
	double meanY, double stdevX, double stdevY, int length){

	double sum = 0;

	for(int i = 0; i < length; i++){
		sum += (arrayX[i] - meanX) * (arrayY[i] - meanY);
	}

	return sum / (stdevX * stdevY * (length - 1));
}

double mean(double* arrayIn, int arrayLength){
	double sum = 0;

	for(int i = 0; i < arrayLength; i++){
		sum += arrayIn[i];
	}

	return sum / arrayLength;
}
