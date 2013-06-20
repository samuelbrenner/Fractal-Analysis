/** Fractal analysis module utilizing boxcounting to determine 
	the fractal dimension of a shape in the input text file.
**/



#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
#include "regressionModule.h"

using namespace std;

const char* fileName = "fractal_data/Juliadim2_4096.txt";

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
 	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			printf("%3.3f ", arrayIn[i][j]);
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
	for(int i = 0; i < HEIGHT; i += boxDimension){
		for(int j = 0; j < WIDTH; j += boxDimension){
			for(int k = 0; k < DEPTH; k += boxDimensionZ){
				int boxSum = 0;


				//sums each box
				for(int boxSumX = 0; boxSumX < boxDimension; boxSumX++){
					for(int boxSumY = 0; boxSumY < boxDimension; boxSumY++){
						for(int boxSumZ = 0; boxSumZ < boxDimensionZ; boxSumZ++){
							boxSum += arrayIn[boxSumX + i][boxSumY + j][boxSumZ + k];
						}
					}
				}

				if(boxSum > 0){
					numberFilled++;
				}
			}
		}
	}
	/*printf("%s%d\n%s%d\n%s%d\n\n", "level: ", level, 
	"--box dimension: ", boxDimension, "--filled boxes: ", numberFilled);		
	*/
	return log2(numberFilled);
}

int main () {
 ifstream myfile (fileName);
 
 if(!(myfile.is_open())){
 	cout << "please open the right file" << endl;
 	return -1;

 }
 string width;
 string height;
 string depth;
 string line;


 if(myfile.is_open()){
 	getline (myfile, height);
 	getline (myfile, width);
 	getline (myfile, depth);
 	
 }

 int HEIGHT = convertToInt(height);
 int WIDTH = convertToInt(width);
 int DEPTH = convertToInt(depth);

 printf("\n\n%s%d\n%s%d\n%s%d\n", "height: ", HEIGHT, "width: ", WIDTH, "depth: ", DEPTH);

 //allocate array
 int*** elements;
 elements = new int**[HEIGHT];
 
 for(int i = 0; i < HEIGHT; i ++){
 	elements[i] = new int*[WIDTH];
 	for(int j = 0; j < WIDTH; j++){
 		elements[i][j] = new int[DEPTH];
 	}
 }

 //input to array
 for(int k = 0; k < DEPTH; k++){
	for(int i = 0; i < HEIGHT; i++){
	 	getline(myfile, line);
	 	stringstream convert(line);
	 	for(int j = 0; j < WIDTH; j++){
	 		int value;
	 		convert >> value;
	 		elements[i][j][k] = value;
	 	}
	}
 }

 //printArray(elements, HEIGHT, WIDTH);

 int LOWESTLEVEL = 0;

 //initialize out-array
 int largestDimension = fmax(HEIGHT, fmax(WIDTH, DEPTH));
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

 printf("\n\n%s%s\n%s%.5f\n\n", "Curve: ", fileName, "Dimension: ", slope(outDataArray, outArrayLength));

  myfile.close();

 delete[] elements;
 delete[] outDataArray;
 

  return 0;
}