/** Fractal analysis module utilizing boxcounting to determine 
	the fractal dimension of a shape in the input text/binary file.

	Prints to terminal:
		- the results at each level of analysis
		- the overall dimension as determined by least-squares regression
		- an R^2 value
		
	@author Samuel Brenner
	@version July 11, 2013

**/



#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
#include "regressionModule.h"
#include "dataReader.h"
#include "interpolation.h"

using namespace std;

void printArray(int** arrayIn, int HEIGHT, int WIDTH){
	cout << endl;
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			printf("%3d", arrayIn[i][j]);
		}
		printf("\n");
	 }
}

void printArray(double** arrayIn, double HEIGHT, double WIDTH){
	cout << endl;
	printf("%7s%7s\n", "level", "log(n)");
 	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			printf("%7.3f ", arrayIn[i][j]);
		}
		printf("\n");
 	}
}

void printToFile(double** arrayIn, int HEIGHT, int WIDTH, double slope, double yint, char* outFileName){
	FILE * pFile;
	pFile = fopen(outFileName, "w");
	fprintf(pFile, "slope: %f\nintercept: %f\n", slope, yint);
	for(int i = HEIGHT - 1; i >= 0; i--){
		for(int j = 0; j < WIDTH; j++){
			fprintf(pFile, "%-2.6f ", arrayIn[i][j]);
		}
		fprintf(pFile, "\n");
	}
	fclose(pFile);
}

void printToFile(int*** arrayIn, int HEIGHT, int WIDTH, char* outFileName){
	FILE * pFile;
	pFile = fopen(outFileName, "w");
	for(int i = HEIGHT - 1; i >= 0; i--){
		for(int j = 0; j < WIDTH; j++){
			fprintf(pFile, "%d ", arrayIn[i][j][0]);
		}
		fprintf(pFile, "\n");
	}
	fclose(pFile);
}

/**
	Returns the log base 2 of the number of cells filled in a given level
	of fractal analysis.
	@param arrayIn is the 2-3-D array of integers that contains the data
	@param HEIGHT
	@param WIDTH
	@param DPETH
	@param level is the level of analysis to be performed. Level 0, for example, 
	examines only the individual data points, whereas at level 1 they are merged
	into boxes of side length 2^1, and for level l size 2^l.
	@return log base 2 of the number of cells filled in a given level.

**/
double boxCounting(int*** arrayIn, int HEIGHT, int WIDTH, int DEPTH, int level){
	int numberFilled = 0; //number of boxes with an element of the figure
	int boxDimension = (int) pow(2, level);
	int boxDimensionZ;

	if(DEPTH != 1){
		boxDimensionZ = boxDimension;
	}
	else{
		boxDimensionZ = 1;
	}
	//iterates through all boxes
	//cout << "here!" << endl;
	for(int i = 0; i < HEIGHT; i += boxDimension){
		for(int j = 0; j < WIDTH; j += boxDimension){
			for(int k = 0; k < DEPTH; k += boxDimensionZ){
				int boxSum = 0;


				//sums each box
				for(int boxSumX = 0; boxSumX < boxDimension; boxSumX++){
					for(int boxSumY = 0; boxSumY < boxDimension; boxSumY++){
						for(int boxSumZ = 0; boxSumZ < boxDimensionZ; boxSumZ++){
							//This is to deal with dimensions that aren't powers of two.
							//if(boxSumX + i >= HEIGHT || boxSumY + j >= WIDTH || boxSumZ + k >= DEPTH){ 
							//	cout << endl << "Dimensions must be powers of two!" << endl;
							//	boxSum += 0;
							//}
							//else{
								boxSum += arrayIn[boxSumX + i][boxSumY + j][boxSumZ + k];
							//}
						}
					}
				}

				if(boxSum > 0){
					numberFilled++;
				}

			}
		}
	}
	printf("%s%d\n%s%d\n%s%d\n\n", "level: ", level, 
	"--box dimension: ", boxDimension, "--filled boxes: ", numberFilled);		

	return log2(numberFilled);
}

int main (int argc, char* argv[]) {
	char* outFileName = argv[2];
	char* inFileName = argv[1];
	int HEIGHT, WIDTH, DEPTH;
	double*** elements;
	bool haveZeros = false;
	double arraySum;
	int*** elementsInterpolated;

	//elements = dataReaderASCII<double>(inFileName, HEIGHT, WIDTH, DEPTH, haveZeros, arraySum);
	elements = dataReaderBinary<double>(inFileName, HEIGHT, WIDTH, DEPTH, haveZeros, arraySum); //for reading in binary data
	elementsInterpolated = interpolate(elements, HEIGHT, WIDTH, DEPTH, 0.5);
	//printToFile(elementsInterpolated, HEIGHT, WIDTH);

	int LOWESTLEVEL = 0;

	//initialize out-array
	int largestDimension = fmin(HEIGHT, WIDTH);
	if(DEPTH > 1){
		largestDimension = fmin(largestDimension, DEPTH);
	}
	int outArrayLength = int(log2(largestDimension) - LOWESTLEVEL + 1);
	double** outDataArray = new double* [outArrayLength];

	//printf("\n\n%d\n\n", outArrayLength);

	for(int i = 0; i < outArrayLength; i++){
		outDataArray[i] = new double[2];
	}

	for(int k = 0; k < outArrayLength; k++)
	{
		outDataArray[k][0] = outArrayLength - 1 - (k + LOWESTLEVEL);
		outDataArray[k][1] = boxCounting(elementsInterpolated, HEIGHT, WIDTH, DEPTH, k + LOWESTLEVEL);
	}

	printArray(outDataArray, outArrayLength, 2);

	double* regressionArray = new double[3];

	slope(outDataArray, outArrayLength, regressionArray);

	printf("\n\n%s%s\n\n%s%.5f\n%s%1.3f\n\n", "Curve: ", inFileName, "Dimension: ", regressionArray[0], "R^2: ", regressionArray[1]);

	printToFile(outDataArray, outArrayLength, 2, regressionArray[0], regressionArray[2], outFileName);

	printToFile(elementsInterpolated, HEIGHT, WIDTH, "elementsInterpolated.txt");

	delete[] elements;
	delete[] elementsInterpolated;
	delete[] outDataArray;
	delete[] regressionArray;

	return 0;
}