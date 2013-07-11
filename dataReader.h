/** 
	Module to read in the data to be used in fractal and multifractal analysis.

	Implemented in multifracBoxCounter3D.cpp:
		Multifractal analysis module utilizing boxcounting to determine 
		the multifractal spectrum of a measure in the input text/binary file.

		Prints the data that forms the multifractal spectrum to a text file
		that can later be analyzed in Matlab or another visualization program.

		The algorithm used is described in:
			A. Chhabra and R. V. Jensen, Phys. Rev. Lett. 62, 1330 (1989).

		@author Samuel Brenner
		@version July 11, 2013

	Implemented in boxCounter3D.cpp:
		Fractal analysis module utilizing boxcounting to determine 
		the fractal dimension of a shape in the input text/binary file.

		Prints to terminal:
			- the results at each level of analysis
			- the overall dimension as determined by least-squares regression
			- an R^2 value

		@author Samuel Brenner
		@version July 11, 2013

	@author Samuel Brenner
	@version July 11, 2013
**/
#ifndef dataReader_h
#define dataReader_h
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
using namespace std;

template <class T>
T*** dataReaderASCII(const char* fileName, int& HEIGHT, int& WIDTH, int& DEPTH, bool& haveZeros, T& arraySum);
template <class T>
T*** dataReaderBinary(const char* fileName, int& HEIGHT, int& WIDTH, int& DEPTH, bool& haveZeros, T& arraySum){
	ifstream myfile (fileName, ios::in | ios::binary);
	char buffer[100];

	if(myfile.is_open()){
		//myfile.seekg(0);
		myfile.read((char*)&HEIGHT, sizeof(int)); //Read in height, which should be an int (sizeof(int) bytes long)
		myfile.read((char*)&WIDTH, sizeof(int));	//read in width
		myfile.read((char*)&DEPTH, sizeof(int));	//read in depth
	}

	printf("\n\n%s%d\n%s%d\n%s%d\n\n", "height: ", HEIGHT, "width: ", WIDTH, "depth: ", DEPTH);

	//allocate array
	T*** elements;
	elements = new T**[HEIGHT];

	for(int i = 0; i < HEIGHT; i ++){
		elements[i] = new T*[WIDTH];
		for(int j = 0; j < WIDTH; j++){
			elements[i][j] = new T[DEPTH];
		}
	}

	arraySum = 0.0;
	//input to array
	for(int k = 0; k < DEPTH; k++){
		for(int i = 0; i < HEIGHT; i++){
		 	for(int j = 0; j < WIDTH; j++){
		 		myfile.read((char*)&elements[i][j][k], sizeof(T));
		 		arraySum += elements[i][j][k];
		 		if (elements[i][j][k] == 0){
		 			haveZeros = true;
		 		}
		 	}
		}
	}
	myfile.close();

	return elements;
}

int convertToInt(string stringIn){
	int result;
	stringstream convert(stringIn);
 	convert >> result;
 	return result;
}

template <class T>

T*** dataReaderASCII(const char* fileName, int& HEIGHT, int& WIDTH, int& DEPTH, bool& haveZeros, T& arraySum){
	ifstream myfile (fileName);
	string width;
	string height;
	string depth;
	string line;


	if(myfile.is_open()){
		getline (myfile, height);
		getline (myfile, width);
		getline (myfile, depth);
		
	}

	HEIGHT = convertToInt(height);
	WIDTH = convertToInt(width);
	DEPTH = convertToInt(depth);
	printf("\n\n%s%d\n%s%d\n%s%d\n\n", "height: ", HEIGHT, "width: ", WIDTH, "depth: ", DEPTH);

	T*** elements;
	elements = new T**[HEIGHT];

	for(int i = 0; i < HEIGHT; i ++){
		elements[i] = new T*[WIDTH];
		for(int j = 0; j < WIDTH; j++){
			elements[i][j] = new T[DEPTH];
		}
	}

	//input to array
	for(int k = 0; k < DEPTH; k++){
		for(int i = 0; i < HEIGHT; i++){
			//cout << i << endl;
		 	getline(myfile, line);					
		 	stringstream convert(line);
		 	for(int j = 0; j < WIDTH; j++){
		 		T value;
		 		convert >> value;
		 		elements[i][j][k] = value;
		 		arraySum += value;
		 		if (elements[i][j][k] == 0){
		 			haveZeros = true;
		 		}
		 	}
		}
	}
	return elements;
}

#endif