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
				if(arrayIn[i][j][k] == valueToFind){
					arrayOut[i][j][k] = 1;
				}
				else{
					arrayOut[i][j][k] = 0;
				}
			}
		}
	}

	for(int i = 1; i < HEIGHT - 1; i++){
		for(int j = 1; j < WIDTH -1; j++){
			if(arrayIn[i][j][1] < valueToFind){
				if(arrayIn[i + 1][j][1] > valueToFind){
					
				}
				else if(arrayIn[i][j + 1][1] > valueToFind){

				}
				else if(arrayIn[i][j - 1][1] > valueToFind){

				}
				else if(arrayIn[i - 1][j][1] > valueToFind){

				}
			}
		}
	}





}





#endif