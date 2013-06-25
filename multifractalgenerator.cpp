//Program to generate fractals in text.
#include <fstream>
#include <iostream>
#include <math.h>
#include <random>


int HEIGHT = 1024;
int WIDTH = 1024;


point** fractalize(point** fractalArray){
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			fractalArray[i][j].probability = 
			rand() % pow(HEIGHT, 2);

	
}


struct point{
	double probability;
	int value; 
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
			fractalArray[i][j] = 0;
		}
	}

	//fill array with fractal shape
	fractalArray = fractalize(fractalArray);





	delete[] fractalArray;
}

