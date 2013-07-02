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
#include "include/libstat.h"

using namespace std;


const char* fileName = "binomial.txt";

int convertToInt(string stringIn){
	int result;
	stringstream convert(stringIn);
 	convert >> result;
 	return result;
}

void printArray(int* arrayIn, int HEIGHT, int WIDTH){
	cout << endl;
	for(int i = 0; i < HEIGHT; i++){
		//for(int j = 0; j < WIDTH; j++){
			printf("%7d", arrayIn[i]);
		//}
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

struct Nalpha{
	double alpha;
	double count;
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
double** boxCounting(double* arrayIn, int HEIGHT, int WIDTH, int DEPTH, int level, int& outArrayLength){
	using namespace Statistics;
	int boxDimension = (int) pow(2, level);
	int boxDimensionZ;

	if(DEPTH != 1){
		boxDimensionZ = boxDimension;
	}
	else{
		boxDimensionZ = 1;
	}

	//creates Histogram object
	Histogram hist;
	int nDataPts = HEIGHT / boxDimension;
	int nBins = 100;
	double* histogramArray = new double[nDataPts];
	double minVal = 0.0;
	double maxVal = 0.0;
	int arrayCounter = 0;

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
		//for(int j = 0; j < WIDTH; j += boxDimension){
			//for(int k = 0; k < DEPTH; k += boxDimensionZ){
				double boxSum = 0;

				//sums each box
				for(int boxSumX = 0; boxSumX < boxDimension; boxSumX++){
					//for(int boxSumY = 0; boxSumY < boxDimension; boxSumY++){
						//for(int boxSumZ = 0; boxSumZ < boxDimensionZ; boxSumZ++){
							
							//This is to deal with dimensions that aren't powers of two.
								//if(boxSumX + i >= HEIGHT || boxSumY + j >= WIDTH || boxSumZ + k >= DEPTH){ 
								//	cout << endl << "Dimensions must be powers of two!" << endl;				
								//	boxSum += 0;
								//}
								//else{
								boxSum += arrayIn[boxSumX + i];//[boxSumY + j][boxSumZ + k];
								//}
						//}
					//}
				}
				histogramArray[arrayCounter] = boxSum;
				arrayCounter++;
				//coarseContents.push_back(boxSum);
			//}
		//}
	}

	computeMinMax(histogramArray, nDataPts, minVal, maxVal);
	double binRange[] = {minVal, maxVal};
	Histogram::HistObj* onlineHist 
		= hist.createStaticHistogram(binRange, nBins, "onlineHist", Histogram::SPACING_LIN);
	
	for(int i = 0; i < nDataPts; i++){
		hist.addDatum(onlineHist, histogramArray[i]);
	}

	//counts the number of non-empty bins
	int nFullBins = 0;

	for(int i = 0; i < nBins; i++){
		if(hist.getBinCount(onlineHist, i) != 0){
			nFullBins++;
		}
	}


	outArrayLength = nFullBins;

	//creates array to hold falpha
	double** falpha = new double*[nFullBins];
	for(int i = 0; i < nFullBins; i++){
		falpha[i] = new double[2];
	}

	int falphaIndexFilledSoFar = 0;
	//fills falpha
	for(int i = 0; i < nBins; i++){
		if(hist.getBinCount(onlineHist, i) != 0){
			//level is already log2(boxsize)
			falpha[falphaIndexFilledSoFar][0] = log2(hist.getBinEdges(onlineHist, i))/double(level); //alpha
			falpha[falphaIndexFilledSoFar][1] = log2(hist.getBinCount(onlineHist, i))/double(level); //falpha
			falphaIndexFilledSoFar++;
		}
	}

	//hist.printObject(std::cout);

	

	delete[] histogramArray;





	//places coarseArray contents into a vector for counting.
	
	/*for (int i = 0; i < coarseHeight; i++){
			for (int j = 0; j < coarseWidth; j++){
				for(int k = 0; k < coarseDepth; k++){
					coarseContents.push_back(coarseArray[i][j][k]);
				}
			}
		}*/

	//makes frequency vector
	/*vector<Nalpha> frequencyVector;
		while(coarseContents.size() > 0){
			double measure = coarseContents[0];
			int num_alpha = 0;
			while (std::find(coarseContents.begin(), coarseContents.end(), measure) != coarseContents.end()){ 
				coarseContents.erase(std::find(coarseContents.begin(), coarseContents.end(), measure));
				num_alpha++;
			}
			Nalpha nalpha;
			nalpha.alpha = log2(measure)/double(level);
			nalpha.count = num_alpha;
			frequencyVector.push_back(nalpha);
		}*/
/*
	cout << "FVector size: " << frequencyVector.size() << endl;
		outArrayLength = frequencyVector.size();
		cout << "outArrayLength: " <<outArrayLength <<endl;
		

	double** falpha = new double*[outArrayLength];
	for(int i = 0; i < outArrayLength; i++){
		falpha[i] = new double[2];
	}


	for(int i = 0; i < outArrayLength; i++){
		falpha[i][0] = frequencyVector[i].alpha;
		falpha[i][1] =  log2(frequencyVector[i].count)/double(level);
	}

	
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
	
	
	//delete[] coarseArray;
	*/
	return falpha;	

}

int main () {
	ifstream myfile (fileName);

	if(!(myfile.is_open())){
		cout << "please open the right file" << endl;
		return -1;
	}
	//string width;
	string height;
	//string depth;
	string line;


	if(myfile.is_open()){
		getline (myfile, height);
		//getline (myfile, width);
		//getline (myfile, depth);
		
	}

	int HEIGHT = convertToInt(height);
	int WIDTH = 1;
	int DEPTH = 1;
	//int WIDTH = convertToInt(width);
	//int DEPTH = convertToInt(depth);

	printf("\n\n%s%d\n%s%d\n%s%d\n\n", "height: ", HEIGHT);// "width: ", WIDTH, "depth: ", DEPTH);

	//allocate array
	double* elements;
	elements = new double[HEIGHT];

	/*for(int i = 0; i < HEIGHT; i ++){
		elements[i] = new double*[WIDTH];
		for(int j = 0; j < WIDTH; j++){
			elements[i][j] = new double[DEPTH];
		}
	}*/

	//input to array
	//for(int k = 0; k < DEPTH; k++){
		for(int i = 0; i < HEIGHT; i++){
			//cout << i << endl ;
		 	getline(myfile, line);					//will implement getchar later to read in one character at a time, and eventually binary files
		 	stringstream convert(line);
		 	//for(int j = 0; j < WIDTH; j++){
		 		double value;
		 		convert >> value;
		 		elements[i] = value;
		 	//}
		}
	//}

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

	int LOWESTLEVEL = 1;
	int outArrayLength = 0;

	for(int k = 0; k < log2(HEIGHT) - LOWESTLEVEL; k++){
		cout << endl << "Level: " << k + LOWESTLEVEL << endl;
		double** falpha = boxCounting(elements, HEIGHT, WIDTH, DEPTH, k + LOWESTLEVEL, outArrayLength);
		printArray(falpha, outArrayLength, 2);
		printToFile(falpha, k + LOWESTLEVEL, outArrayLength);
	}

	myfile.close();

	delete[] elements;
	return 0;
}
