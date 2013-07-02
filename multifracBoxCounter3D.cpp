/** Fractal analysis module utilizing boxcounting to determine 
	the fractal dimension of a shape in the input text file.
**/
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
//#include "regressionModule.h"
#include <vector>
#include <algorithm>

using namespace std;


const char* fileName = "multifractal.txt";
double qMin = -10;
double qMax = 10;

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
			printf("%7d", arrayIn[i][j]);
		}
		printf("\n");
	 }
}

void printArray(double** arrayIn, int arrayHeight, int WIDTH){
	cout << endl;
 	for(int i = 0; i < arrayHeight; i++){
		for(int j = 0; j < WIDTH; j++){
			printf("%3.3f ", arrayIn[i][j]);
		}
		printf("\n");
 	}
}

void printToFile(double** arrayIn, int level, int HEIGHT){
	FILE * pFile;
	char* fileOutName = new char[20];
	sprintf(fileOutName, "%s%d%s", "falpha_level_", level, ".txt");
	pFile = fopen(fileOutName, "w");
	for(int i = 0; i < HEIGHT; i++){
		fprintf(pFile, "%.8f %.8f", arrayIn[i][0], arrayIn[i][1]);
		fprintf(pFile, "\n");
	}
	fclose(pFile);
	delete[] fileOutName;
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
double** boxCounting(double*** arrayIn, int HEIGHT, int WIDTH, int DEPTH, int level){
	int boxDimension = (int) pow(2, level);
	int boxDimensionZ;

	if(DEPTH != 1){
		boxDimensionZ = boxDimension;
	}
	else{
		boxDimensionZ = 1;
	}

	int nDataPts = HEIGHT * WIDTH * DEPTH / pow(boxDimension, 2) / boxDimensionZ;
	int falphaSize = qMax - qMin + 1;

	//creates array to hold falpha
	double** falpha = new double*[falphaSize];
	for(int i = 0; i < qMax - qMin + 1; i++){
		falpha[i] = new double[2];
	}

	for(double q = qMin; q <= qMax; q++){
		double* probability = new double[nDataPts];
		double sumOfProbabilitiesQthMoment = 0.0;
		int arrayCounter = 0;
		double fOfQ = 0.0;
		double alphaOfQ = 0.0;

		//vector<double> coarseContents;
		//creating array of course-grained data
		/*int coarseHeight = HEIGHT / boxDimension;
			int coarseWidth = WIDTH / boxDimension;
			int coarseDepth = DEPTH / boxDimensionZ;
			
			double*** coarseArray = new double**[coarseHeight];

			for(int i = 0; i < coarseHeight; i++){
				coarseArray[i] = new double*[coarseWidth];
				for(int j = 0; j < coarseWidth; j++){
					coarseArray[i][j] = new double[coarseDepth];
				}		
			}*/

		//iterates through all boxes
		for(int i = 0; i < HEIGHT; i += boxDimension){
			for(int j = 0; j < WIDTH; j += boxDimension){
				for(int k = 0; k < DEPTH; k += boxDimensionZ){
					double boxSum = 0;

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
					probability[arrayCounter] = boxSum;
					arrayCounter++;
					//coarseContents.push_back(boxSum);
				}
			}
		}
	
	
		for(int i = 0; i < nDataPts; i++){
			sumOfProbabilitiesQthMoment += pow(probability[i], q);
		}

		double log2size = log2(double(boxDimension) / HEIGHT);

		for(int i = 0; i < nDataPts; i++){
			double normalizedMeasure = pow(probability[i], q) / sumOfProbabilitiesQthMoment;
			//cout << log2(normalizedMeasure) << endl;
			fOfQ += normalizedMeasure * log2(normalizedMeasure);
			alphaOfQ += normalizedMeasure * log2(probability[i]);
		}

		falpha[int(q - qMin)][0] = alphaOfQ / log2size;
		falpha[int(q - qMin)][1] = fOfQ / log2size;
		delete[] probability;
	}

	return falpha;
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

	printf("\n\n%s%d\n%s%d\n%s%d\n\n", "height: ", HEIGHT, "width: ", WIDTH, "depth: ", DEPTH);

	//allocate array
	double*** elements;
	elements = new double**[HEIGHT];

	for(int i = 0; i < HEIGHT; i ++){
		elements[i] = new double*[WIDTH];
		for(int j = 0; j < WIDTH; j++){
			elements[i][j] = new double[DEPTH];
		}
	}

	//input to array
	for(int k = 0; k < DEPTH; k++){
		for(int i = 0; i < HEIGHT; i++){
			//cout << i << endl ;
		 	getline(myfile, line);					//will implement getchar later to read in one character at a time, and eventually binary files
		 	stringstream convert(line);
		 	for(int j = 0; j < WIDTH; j++){
		 		double value;
		 		convert >> value;
		 		elements[i][j][k] = value;
		 	}
		}
	}

	/* Print arrayIn to test that it works
		int** elementsForPrinting = new int*[HEIGHT];

		for(int i = 0; i < HEIGHT; i++){
			elementsForPrinting[i] = new int[WIDTH];
		}

		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){
				elementsForPrinting[i][j] = elements[i][j][0];
			}
		}

		printArray(elementsForPrinting, HEIGHT, WIDTH);

		delete[] elementsForPrinting;
	*/

	int LOWESTLEVEL = 0;

	for(int k = 0; k < log2(HEIGHT) - LOWESTLEVEL; k++){
		cout << endl << "Level: " << k + LOWESTLEVEL << endl;
		double** falpha = boxCounting(elements, HEIGHT, WIDTH, DEPTH, k + LOWESTLEVEL);
		printArray(falpha, qMax - qMin + 1, 2);
		printToFile(falpha, k + LOWESTLEVEL, qMax - qMin + 1);
	}

	myfile.close();

	delete[] elements;
	return 0;
}
