//Program to generate fractals in text.
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>

using namespace std;

int HEIGHT = pow(2, 9);
int WIDTH = HEIGHT;
int DEPTH = 1;
//double normalizer = 1;//double(pow(5.0, log2(HEIGHT)));

struct point{
	double probability;
	int value; 
};

void assignProbabilities(point** fractalArray){
	double fractalSum = 0.0;
	for(int levelDivision = HEIGHT; levelDivision > 1; levelDivision /= 2){
		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){

				if((i % levelDivision >= (levelDivision / 2)) && (j % levelDivision >= (levelDivision / 2))){
					fractalArray[i][j].probability *= 2.0 / 5.0;
				}
				else{
					fractalArray[i][j].probability *= 1.0 / 5.0;
				}

				fractalSum += fractalArray[i][j].probability;

			}
		}
	}
	double fractalSumNew = 0.0;

	//divide each element by a certain factor so that the total probability is still one.
	
	//for(int i = 0; i < HEIGHT; i++){
		//for(int j = 0; j < WIDTH; j++){
		//	fractalArray[i][j].probability /= normalizer;
		//	fractalSumNew += fractalArray[i][j].probability;
	//	}
	//}
	//cout << normalizer << endl;
	//cout << fractalSumNew << endl;
}



void printToTerminal(point** arrayIn){
	cout << endl;
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			printf("%-.8f ", arrayIn[i][j].probability);
		}
		printf("\n\n");
	 }
}

void printToFile(point** arrayIn){
	ofstream myFile("multifractal.bin", ios::out | ios::binary);
	myFile.write((char*)&HEIGHT, sizeof(int));


	cout << (char*)&HEIGHT << endl;


	myFile.write((char*)&WIDTH, sizeof(int));
	myFile.write((char*)&DEPTH, sizeof(int));
	//fprintf(pFile, "%d\n%d\n1\n", HEIGHT, WIDTH);
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			myFile.write((char*)&arrayIn[i][j].probability, sizeof(double));
		}
	}
	myFile.close();
}


int main(){
	//initialize array
	point** fractalArray = new point*[HEIGHT];
	for(int i = 0; i < HEIGHT; i++){
		fractalArray[i] = new point[WIDTH];
	}

	//fill array with zeroes
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			fractalArray[i][j].probability = 1;
		}
	}

	//fill array with fractal shape
	assignProbabilities(fractalArray);

	//printToTerminal(fractalArray);
	printToFile(fractalArray);





	delete[] fractalArray;
	return 0;
}

