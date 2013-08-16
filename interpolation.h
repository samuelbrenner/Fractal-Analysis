/**
	Module to interpolate the isocontour at some pre-specified value inside a 2- or 3-D array.

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

#ifndef interpolation_h
#define interpolation_h

int*** interpolate(double*** arrayIn, int HEIGHT, int WIDTH, int DEPTH, double valueToFind){
	//Declare and initialize arrayOut. If any values in the arrayIn happen to be the valueToFind,
	//we'll initialize the corresponding arrayOut to a 1; otherwise it'll be a 0.
	int*** arrayOut = new int**[HEIGHT];
	for(int i = 0; i < HEIGHT; i++){
		arrayOut[i] = new int*[WIDTH];
		for(int j = 0; j < WIDTH; j++){
			arrayOut[i][j] = new int[DEPTH];
			for(int k = 0; k < DEPTH; k++){
				//performs a preliminary check so that we don't miss any values that are exactly == valueToFind
				if(arrayIn[i][j][k] == valueToFind){
					arrayOut[i][j][k] = 1;
				}
				else{
					arrayOut[i][j][k] = 0;
				}
			}
		}
	}

	//Makes the interpolater able to handle planar data
	int startingDepthIndex = 0;
	if(DEPTH != 1){
		startingDepthIndex = 1;
	}
	else{
		DEPTH++;
	}

	/*
		Iterates over all entries in the array that aren't on the edge of the array, unless the array is 2D: for 2D
		arrays the program ignores the edge condition in the third dimension.

		For each entry analyzed, we check to see if the value is lower than valueToFind. If so, the neighbors on all 
		six sides (four if planar data) are checked against it to determine if there is some crossing over valueToFind
		in between the two. Then we determine which cell should contain that crossing and assign it a 1 in the 
		corresponding cell of the outArray.
	*/
	for(int i = 1; i < HEIGHT - 1; i++){
		for(int j = 1; j < WIDTH -1; j++){
			for(int k = startingDepthIndex; k < DEPTH - 1; k++){
				if(arrayIn[i][j][k] < valueToFind){
					if(arrayIn[i + 1][j][k] > valueToFind){
						if(int((valueToFind - arrayIn[i][j][k]) / (arrayIn[i + 1][j][k] - arrayIn[i][j][k])) == 0){
							arrayOut[i][j][k] = 1;
						}
						else{
							arrayOut[i + 1][j][k] = 1;
						}
					}
					if(arrayIn[i][j + 1][k] > valueToFind){
						if(int((valueToFind - arrayIn[i][j][k]) / (arrayIn[i][j + 1][k] - arrayIn[i][j][k])) == 0){
							arrayOut[i][j][k] = 1;
						}
						else{
							arrayOut[i][j + 1][k] = 1;
						}
					}
					if(arrayIn[i][j - 1][k] > valueToFind){
						if(int((valueToFind - arrayIn[i][j][k]) / (arrayIn[i][j - 1][k] - arrayIn[i][j][k])) == 0){
							arrayOut[i][j][k] = 1;
						}
						else{
							arrayOut[i][j - 1][k] = 1;
						}
					}
					if(arrayIn[i - 1][j][k] > valueToFind){
						if(int((valueToFind - arrayIn[i][j][k]) / (arrayIn[i - 1][j][k] - arrayIn[i][j][k])) == 0){
							arrayOut[i][j][k] = 1;
						}
						else{
							arrayOut[i - 1][j][k] = 1;
						}
					}
					if(arrayIn[i][j][k + 1] > valueToFind){
						if(int((valueToFind - arrayIn[i][j][k]) / (arrayIn[i][j][k + 1] - arrayIn[i][j][k])) == 0){
							arrayOut[i][j][k] = 1;
						}
						else{
							arrayOut[i][j][k + 1] = 1;
						}
					}
					if(arrayIn[i][j][k - 1] > valueToFind){
						if(int((valueToFind - arrayIn[i][j][k]) / (arrayIn[i][j][k - 1] - arrayIn[i][j][k])) == 0){
							arrayOut[i][j][k] = 1;
						}
						else{
							arrayOut[i][j][k - 1] = 1;
						}
					}

				}
			}
		}
	}




return arrayOut;
}


int*** makeInt(double*** arrayIn, int HEIGHT, int WIDTH, int DEPTH){
	//Declare and initialize arrayOut. If any values in the arrayIn happen to be the valueToFind,
	//we'll initialize the corresponding arrayOut to a 1; otherwise it'll be a 0.
	int*** arrayOut = new int**[HEIGHT];
	for(int i = 0; i < HEIGHT; i++){
		arrayOut[i] = new int*[WIDTH];
		for(int j = 0; j < WIDTH; j++){
			arrayOut[i][j] = new int[DEPTH];
			for(int k = 0; k < DEPTH; k++){
				//performs a preliminary check so that we don't miss any values that are exactly == valueToFind
				if(arrayIn[i][j][k] == 0.0){
					arrayOut[i][j][k] = 0;
				}
				else{
					arrayOut[i][j][k] = 1;
				}
			}
		}
	}

	//Makes the interpolater able to handle planar data
	return arrayOut;
}




#endif