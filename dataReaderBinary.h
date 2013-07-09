#ifndef dataReaderBinary_h
#define dataReaderBinary_h
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
using namespace std;

template <class T>

T*** dataReaderBinary(const char* fileName, int& HEIGHT, int& WIDTH, int& DEPTH, bool& haveZeros, T& arraySum){
	ifstream myfile (fileName, ios::in | ios::binary);
	char buffer[100];

	if(myfile.is_open()){
		//myfile.seekg(0);
		myfile.read((char*)&HEIGHT, sizeof(int)); //Read in height, which should be an int (sizeof(int) bytes long)
		cout << "THE HEIGHT IS: " << HEIGHT << endl << "myfile.gcount() " << myfile.gcount();
		myfile.read((char*)&WIDTH, sizeof(int));
		myfile.read((char*)&DEPTH, sizeof(int));
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

#endif