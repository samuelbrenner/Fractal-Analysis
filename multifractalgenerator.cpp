//Program to generate fractals in text.
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>

using namespace std;

int HEIGHT = 16;
int WIDTH = 16;

struct point{
	double probability;
	int value; 
};

void fractalize(point** fractalArray){
	for(int levelDivision = HEIGHT; levelDivision > 1; levelDivision /= 2){
		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){

				if(i % levelDivision >= (levelDivision / 2) && j % levelDivision >= (levelDivision / 2)){
					fractalArray[i][j].probability *= 0.4;
				}
				else{
					fractalArray[i][j].probability *= 0.2;
				}
			}
		}
	}
}

void printArray(point** arrayIn){
	cout << endl;
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			printf("%3.4f ", arrayIn[i][j].probability);
		}
		printf("\n\n");
	 }
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
	fractalize(fractalArray);

	printArray(fractalArray);





	delete[] fractalArray;
}

