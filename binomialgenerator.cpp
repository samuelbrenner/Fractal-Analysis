//Program to generate fractals in text.
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>

using namespace std;

int HEIGHT = pow(2, 10);

double normalizer = 1;//double(pow(5.0, log2(HEIGHT)));

struct point{
	double probability;
	int value; 
};

void assignProbabilities(point* fractalArray){
	double fractalSum = 0.0;
	for(int levelDivision = HEIGHT; levelDivision > 1; levelDivision /= 2){
		for(int i = 0; i < HEIGHT; i++){
			if(i % levelDivision >= (levelDivision / 2)){
				fractalArray[i].probability *= 0.7;
			}
			else{
				fractalArray[i].probability *= 0.3;
			}

			fractalSum += fractalArray[i].probability;

			
		}
	}
	double fractalSumNew = 0.0;

	//divide each element by a certain factor so that the total probability is still one.
	
	/*for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			fractalArray[i][j].probability /= normalizer;
			fractalSumNew += fractalArray[i][j].probability;
		}
	}*/

	cout << normalizer << endl;
	cout << fractalSumNew << endl;
}



void printToTerminal(point* arrayIn){
	cout << endl;
	for(int i = 0; i < HEIGHT; i++){
		//for(int j = 0; j < WIDTH; j++){
			printf("%-.8f ", arrayIn[i].probability);
		//}
		printf("\n\n");
	 }
}

void printToFile(point* arrayIn){
	FILE * pFile;
	pFile = fopen("binomial.txt", "w");
	fprintf(pFile, "%d\n", HEIGHT);
	for(int i = 0; i < HEIGHT; i++){
		//fprintf(pFile, "%d    ", i); //print indices so we can display easily in Matlab
		fprintf(pFile, "%-.10f ", arrayIn[i].probability);
		fprintf(pFile, "\n");
	}
	fclose(pFile);
}


int main(){
	//initialize array
	point* fractalArray = new point[HEIGHT];

	//fill array with zeroes
	for(int i = 0; i < HEIGHT; i++){
		fractalArray[i].probability = 1;
	}

	//fill array with fractal shape
	assignProbabilities(fractalArray);

	//printToTerminal(fractalArray);
	printToFile(fractalArray);





	delete[] fractalArray;
	return 0;
}

