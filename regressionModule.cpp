#include "regressionModule.h"

#include <math.h>

double stdev(double* arrayIn, double arrayMean, int arrayLength);

double corrCoeff(double* arrayX, double* arrayY, double meanX, 
	double meanY, double stdevX, double stdevY, int length);

double mean(double* arrayIn, int arrayLength);

void slope(double** arrayIn, int arrayLength, double* regressionArray){
	
	double* arrayX = new double[arrayLength];

	for(int i = 0; i < arrayLength; i++){
		arrayX[i] = arrayIn[i][0];
	}

	double* arrayY = new double[arrayLength];
	for(int i = 0; i < arrayLength; i++){
		arrayY[i] = arrayIn[i][1];
	}

	double meanX = mean(arrayX, arrayLength);
	double meanY = mean(arrayY, arrayLength);

	double stdevX = stdev(arrayX, meanX, arrayLength);
	double stdevY = stdev(arrayY, meanY, arrayLength);

	double r = corrCoeff(arrayX, arrayY, meanX, meanY, stdevX, stdevY, arrayLength);

	double slope = r 
		* stdevY / stdevX;


	delete[] arrayX;
 	delete[] arrayY;

 	regressionArray[0] = slope;
 	regressionArray[1] = pow(r, 2);
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
