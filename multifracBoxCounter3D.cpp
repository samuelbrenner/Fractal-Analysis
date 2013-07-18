/** 
	Multifractal analysis module utilizing boxcounting to determine 
	the multifractal spectrum of a measure in the input text/binary file.

	Prints the data that forms the multifractal spectrum to a text file
	that can later be analyzed in Matlab or another visualization program.

	The algorithm used is described in:
		A. Chhabra and R. V. Jensen, Phys. Rev. Lett. 62, 1330 (1989).

	@author Samuel Brenner
	@version July 11, 2013
**/
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
#include <algorithm>
#include "dataReader.h"
#include "dataCorrection.h"

using namespace std;

double qMin = -10;	//minimum and maximum values of the moment used in 
double qMax = 10;
double qIncrement = 1.0; //the step used between each value of q tested.

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

void printToFile(double** arrayIn, int level, int HEIGHT, char* fileOutDirectory){
	FILE * pFile;
	char* fileOutName = new char[100];
	sprintf(fileOutName, "%s%s%d%s", fileOutDirectory, "_falpha_level_", level, ".txt");
	pFile = fopen(fileOutName, "w");
	for(int i = 0; i < HEIGHT; i++){
		fprintf(pFile, "%.8f %.8f", arrayIn[i][0], arrayIn[i][1]);
		fprintf(pFile, "\n");
	}
	fclose(pFile);
	delete[] fileOutName;
}

/**	
	Returns in a double** the data points that make up the plot of f(alpha) vs. alpha.
	The analysis is performed using the method of moments described in Chhabra and Jensen, 
	1989 (Phys. Rev. Lett.).
	@param arrayIn is the 2-/3-D array of doubles that contains the data
	@param HEIGHT
	@param WIDTH
	@param DPETH
	@param level is the level of analysis to be performed. Level 0, for example, 
	examines only the individual data points, whereas at level 1 they are merged
	into boxes of side length 2^1, and for level l size 2^l.
	@return alpha vs. f(alpha)
**/
double** boxCounting(double*** arrayIn, int HEIGHT, int WIDTH, int DEPTH, int level){
	int boxDimension = (int) pow(2, level); //side length of the boxes that we'll use to coarse-grain the data, in pixels.
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

	/**	iterates over all values of q to be tested, where q is the "microscope for exploring different regions of the measure",
		an exaggerating exponent that gives us the qth moment of the measure. We parametrize the relationship f(alpha) vs. alpha
		in terms of q to find functions f(q) and alpha(q). These values are then added to the falpha out-array.
	**/
	for(double q = qMin; q <= qMax; q += qIncrement){
		double* probability = new double[nDataPts]; //an array of all the non-normalized measures taken in.
		double sumOfProbabilitiesQthMoment = 0.0;
		int arrayCounter = 0;
		double fOfQ = 0.0;
		double alphaOfQ = 0.0;

		//iterates through all boxes
		for(int i = 0; i < HEIGHT; i += boxDimension){
			for(int j = 0; j < WIDTH; j += boxDimension){
				for(int k = 0; k < DEPTH; k += boxDimensionZ){
					double boxSum = 0.0;

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
				}
			}
		}
	
		for(int i = 0; i < nDataPts; i++){
			sumOfProbabilitiesQthMoment += pow(probability[i], q); //the denominator in eqn. 6 of Chhabra and Jensen
		}

		double log2size = log2(double(boxDimension) / HEIGHT);

		for(int i = 0; i < nDataPts; i++){
			double normalizedMeasure = pow(probability[i], q) / sumOfProbabilitiesQthMoment; //eqn. 6 of Chhabra and Jensen
			//cout << log2(normalizedMeasure) << endl;
			fOfQ += normalizedMeasure * log2(normalizedMeasure); //the numerator of eqn. 7 of Chhabra and Jensen
			alphaOfQ += normalizedMeasure * log2(probability[i]); //the numerator of eqn. 8 of Chhabra and Jensen
		}

		falpha[int(q - qMin)][0] = alphaOfQ / log2size; //the final divisions in each equation
		falpha[int(q - qMin)][1] = fOfQ / log2size;
		delete[] probability;
	}

	return falpha;
}

int main (int argc, char* argv[]) {
	char* fileInName = argv[1];
	char* fileOutDirectory = fileInName;
    int HEIGHT, WIDTH, DEPTH;
    double*** elements;
    bool haveZeros = false;
    double arraySum;
   
    //elements = dataReaderASCII<double>(fileInName, HEIGHT, WIDTH, DEPTH, haveZeros, arraySum); 
    elements = dataReaderBinary<double>(fileInName, HEIGHT, WIDTH, DEPTH, haveZeros, arraySum); //for reading in binary data

    /**	
    	Corrects the data by removing zeros (does so by adding one to every value in the array)
    	and normalizing the array so that the sum of all the elements is one.
    **/
    dataCorrection<double>(elements, HEIGHT, WIDTH, DEPTH, haveZeros, arraySum);

	int LOWESTLEVEL = 0; 	//the lowest level of coarse-graining, where level == 0 examines each individual pixel as its own box.
							//level = log2(box's side length) so that side length = 1 when level == 0.

	//iterates over all levels to be tested, going from LOWESTLEVEL to the highest possible level permitted by the arrayIn size.
	for(int k = 0; k < log2(HEIGHT) - LOWESTLEVEL; k++){
		cout << endl << "Level: " << k + LOWESTLEVEL << endl;
		double** falpha = boxCounting(elements, HEIGHT, WIDTH, DEPTH, k + LOWESTLEVEL);
		printArray(falpha, qMax - qMin + 1, 2);
		printToFile(falpha, k + LOWESTLEVEL, qMax - qMin + 1, fileOutDirectory); //This spectrum output can then be analyzed in Matlab or another visualization program.
	}

	
	//delete[] buffer;
	delete[] elements;
	return 0;
}
