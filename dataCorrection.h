/** 
	Module to remove zeros from an array and normalize it.
	Implemented in multifracBoxCounter3D.cpp:
		Multifractal analysis module utilizing boxcounting to determine 
		the multifractal spectrum of a measure in the input text/binary file.

		Prints the data that forms the multifractal spectrum to a text file
		that can later be analyzed in Matlab or another visualization program.

		The algorithm used is described in:
			A. Chhabra and R. V. Jensen, Phys. Rev. Lett. 62, 1330 (1989).

		@author Samuel Brenner
		@version July 11, 2013

	@author Samuel Brenner
	@version July 11, 2013
**/
	
#ifndef dataCorrection_h
#define dataCorrection_h
using namespace std;

template <class T>

void dataCorrection (T***& elements, int HEIGHT, int WIDTH, int DEPTH, bool haveZeros, T arraySum){
	//creates new int to deal with normalizing array when there are zeros.
	int arraySumWithCorrection = arraySum;

	if(haveZeros){
		arraySumWithCorrection += HEIGHT * WIDTH * DEPTH;
	}

	//check to see if array is normalized
	if(((arraySum - 1)/10.0 != 0) || haveZeros){
		for(int i = 0; i < HEIGHT; i++){
			for(int j = 0; j < WIDTH; j++){
				for(int k = 0; k < DEPTH; k++){
					//adds one if there's a zero in the array
					if(haveZeros){
						elements[i][j][k]++;
					}
					elements[i][j][k] /= double(arraySumWithCorrection);
				}
			}
		}
	}
}
#endif