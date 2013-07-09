/** Fractal analysis module utilizing boxcounting to determine 
	the fractal dimension of a shape in the input text file.
**/



#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
#include "regressionModule.h"
#include "dataReaderBinary.h"
#include "dataCorrection.h"


using namespace std;

const char* fileName = "c_hdf5_plt_cnt_1000.txt";

int convertToInt(string stringIn){
	int result;
	stringstream convert(stringIn);
 	convert >> result;
 	return result;
}

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
							//if(boxSumX + i >= HEIGHT || boxSumY + j >= WIDTH || boxSumZ + k >= DEPTH){ This is to deal with dimensions that aren't
							//	cout << endl << "Dimensions must be powers of two!" << endl;				powers of two.
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

int main () {
	int HEIGHT, WIDTH, DEPTH;
	int*** elements;
	bool haveZeros = false;
	int arraySum;

	elements = dataReaderBinary<int>(fileName, HEIGHT, WIDTH, DEPTH, haveZeros, arraySum);

	printf("\n\n%s%d\n%s%d\n%s%d\n", "height: ", HEIGHT, "width: ", WIDTH, "depth: ", DEPTH);

	//printArray(elements, HEIGHT, WIDTH);

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
		outDataArray[k][1] = boxCounting(elements, HEIGHT, WIDTH, DEPTH, k + LOWESTLEVEL);
	}

	printArray(outDataArray, outArrayLength, 2);

	double* regressionArray = new double[2];

	slope(outDataArray, outArrayLength, regressionArray);

	printf("\n\n%s%s\n\n%s%.5f\n%s%1.3f\n\n", "Curve: ", fileName, "Dimension: ", regressionArray[0], "R^2: ", regressionArray[1]);

	delete[] elements;
	delete[] outDataArray;


	return 0;
}