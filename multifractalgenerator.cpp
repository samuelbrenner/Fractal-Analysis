//Program to generate fractals in text.
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>

using namespace std;

int HEIGHT = 8;
int WIDTH = 8;

struct point{
	int probability;
	int value; 
};

void assignProbabilities(point** fractalArray){
	for(int levelDivision = HEIGHT; levelDivision > 1; levelDivision /= 2){
		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){

				if((i % levelDivision >= (levelDivision / 2)) && (j % levelDivision >= (levelDivision / 2))){
					fractalArray[i][j].probability *= 2;
				}
				else{
					fractalArray[i][j].probability *= 1;
				}
			}
		}
	}
}



void printToTerminal(point** arrayIn){
	cout << endl;
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			printf("%-3d ", arrayIn[i][j].probability);
		}
		printf("\n\n");
	 }
}

void printToFile(point** arrayIn){
	FILE * pFile;
	pFile = fopen("multifractal.txt", "w");
	fprintf(pFile, "%d\n%d\n1\n", HEIGHT, WIDTH);
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			fprintf(pFile, "%-3d ", arrayIn[i][j].probability);
		}
		fprintf(pFile, "\n");
	}
	fclose(pFile);
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

