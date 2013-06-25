/** Fractal analysis module utilizing boxcounting to determine 
	the fractal dimension of a shape in the input text file.
**/
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
#include "regressionModule.h"
#include <vector>
#include <algorithm>

using namespace std;

const char* fileName = "multifractal.txt";
int outArrayLength;

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

void printArray(double** arrayIn, double HEIGHT, double WIDTH){
	cout << endl;
 	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			printf("%3.3f ", arrayIn[i][j]);
		}
		printf("\n");
 	}
}

struct Nalpha{
	unsigned long alpha;
	unsigned long count;
};


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
double** boxCounting(int*** arrayIn, int HEIGHT, int WIDTH, int DEPTH, int level){
	//return type will eventually be double**
	int boxDimension = (int) pow(2, level);
	int boxDimensionZ;

	if(DEPTH != 1){
		boxDimensionZ = boxDimension;
	}
	else{
		boxDimensionZ = 1;
	}

	//creating array of course-grained data
	int coarseHeight = HEIGHT / boxDimension;
	int coarseWidth = WIDTH / boxDimension;
	int coarseDepth = DEPTH / boxDimensionZ;

	int*** coarseArray = new int**[coarseHeight];

	for(int i = 0; i < coarseHeight; i++){
		coarseArray[i] = new int*[coarseWidth];
		for(int j = 0; j < coarseWidth; j++){
			coarseArray[i][j] = new int[coarseDepth];
		}		
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
				coarseArray[i / boxDimension][j / boxDimension][k / boxDimensionZ] = boxSum;
			}
		}
	}



	//places coarseArray contents into a vector for counting.
	vector<int> coarseContents;
	for (int i = 0; i < coarseHeight; i++){
		for (int j = 0; j < coarseWidth; j++){
			for(int k = 0; k < coarseDepth; k++){
				coarseContents.push_back(coarseArray[i][j][k]);
			}
		}
	}

	//makes frequency vector
	vector<Nalpha> frequencyVector;
	while(coarseContents.size() > 0){
		int frontValue = coarseContents[0];
		unsigned long num_alpha = 0;
		while (std::find(coarseContents.begin(), coarseContents.end(), frontValue) != coarseContents.end()){ 
			coarseContents.erase(std::find(coarseContents.begin(), coarseContents.end(), frontValue));
			num_alpha++;
		}
		Nalpha nalpha;
		nalpha.alpha = frontValue;
		nalpha.count = num_alpha;
		frequencyVector.push_back(nalpha);
	}

	/*print frequencyVector
		int** freqForPrinting = new int*[frequencyVector.size()];
		for(int i = 0; i < frequencyVector.size(); i++){
			freqForPrinting[i] = new int[2];
		}
		for(int i = 0; i < frequencyVector.size(); i++){
			freqForPrinting[i][0] = frequencyVector[i].alpha;
			freqForPrinting[i][1] = frequencyVector[i].count;
		}
		printArray(freqForPrinting, frequencyVector.size(), 2);
		delete[] freqForPrinting;
	*/

	double** falpha = new double*[frequencyVector.size()];
	for(int i = 0; i < frequencyVector.size(); i++){
		falpha[i] = new double[2];
	}

	for(int i = 0; i < frequencyVector.size(); i++){
		falpha[i][0] = frequencyVector[i].alpha;
		falpha[i][1] = log2(frequencyVector[i].count)/level;
	}
	outArrayLength = frequencyVector.size();


	/*
		int** coarseArrayForPrinting = new int*[coarseHeight];
		for(int i = 0; i < coarseHeight; i++){
			coarseArrayForPrinting[i] = new int[coarseWidth];
		}
		for(int i = 0; i < coarseHeight; i++){
			for(int j = 0; j < coarseWidth; j++){
				coarseArrayForPrinting[i][j] = coarseArray[i][j][0];
			}
		}

		printArray(coarseArrayForPrinting, coarseHeight, coarseWidth);
		delete[] coarseArrayForPrinting;
	*/
	delete[] coarseArray;
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
			//cout << i << endl ;
		 	getline(myfile, line);					//will implement getchar later to read in one character at a time, and eventually binary files
		 	stringstream convert(line);
		 	for(int j = 0; j < WIDTH; j++){
		 		int value;
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

	for(int k = 0; k < log2(HEIGHT) - LOWESTLEVEL; k++)
	{
		cout << "Level: " << k;
		printArray(boxCounting(elements, HEIGHT, WIDTH, DEPTH, k + LOWESTLEVEL), outArrayLength, 2);
	}


	//printf("\n\n%s%s\n%s%.5f\n\n", "Curve: ", fileName, "Dimension: ", 
		//slope(outDataArray, outArrayLength));

	myfile.close();

	delete[] elements;
	
	return 0;
}