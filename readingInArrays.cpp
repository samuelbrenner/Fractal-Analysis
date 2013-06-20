#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

int convertToInt(string stringIn){
	int result;
	stringstream convert(stringIn);
 	convert >> result;
 	return result;
}

void printArray(int** arrayIn, int HEIGHT, int WIDTH){
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			printf("%3d", arrayIn[i][j]);
		}
		printf("\n");
	 }
}

void printArray(double** arrayIn, double HEIGHT, double WIDTH){
 	for(int i = 0; i < HEIGHT; i++){
		for(int j = 1; j < WIDTH; j++){
			printf("%3.3f ", arrayIn[i][j]);
		}
		printf("\n");
 	}
}

double boxCounting(int** arrayIn, int HEIGHT, int WIDTH, int level){
	int numberFilled = 0; //number of boxes with an element of the figure
	int boxDimension = (int) pow(2, level);

	//iterates through all boxes
	for(int i = 0; i < HEIGHT; i += boxDimension){
		for(int j = 0; j < WIDTH; j += boxDimension){

			int boxSum = 0;

			//sums each box
			for(int boxSumX = 0; boxSumX < boxDimension; boxSumX++){
				for(int boxSumY = 0; boxSumY < boxDimension; boxSumY++){
					boxSum += arrayIn[boxSumX + i][boxSumY + j];
				}
			}

			if(boxSum > 0){
				numberFilled++;
			}
		}
	}
	/*printf("%s%d\n%s%d\n%s%d\n\n", "level: ", level, 
	"--box dimension: ", boxDimension, "--filled boxes: ", numberFilled);		
	*/
	return log2(numberFilled);
}



int main () {
 ifstream myfile ("line_diagonal_0016.txt");
 
 string width;
 string height;
 string line;

 if(myfile.is_open()){
 	getline (myfile, height);
 	getline (myfile, width);
 	
 }

 int HEIGHT = convertToInt(height);
 int WIDTH = convertToInt(width);


 printf("%s%d%s%d\n", "height: ", HEIGHT, "\nwidth: ", WIDTH);

 //allocate array
 int** elements;
 elements = new int*[HEIGHT];
 
 for(int i = 0; i < HEIGHT; i ++){
 	elements[i] = new int[WIDTH];
 }

 //input to array
 for(int i = 0; i < HEIGHT; i++){
 	getline(myfile, line);
 	stringstream convert(line);
 	for(int j = 0; j < WIDTH; j++){
 		int value;
 		convert >> value;
 		elements[i][j] = value;
 	}
 }

 printArray(elements, HEIGHT, WIDTH);

 int LOWESTLEVEL = 0;

 //initialize out-array
 int outArrayLength = int(log2(HEIGHT)) - LOWESTLEVEL + 1;
 double** outDataArray = new double*[outArrayLength];
 for(int i = 0; i < outArrayLength; i++){
 	outDataArray[i] = new double[2];
 }

 for(int k = 0; k < outArrayLength; k++)
 {
 	outDataArray[k][0] = k + LOWESTLEVEL;
 	outDataArray[k][1] = boxCounting(elements, HEIGHT, WIDTH, k + LOWESTLEVEL);
 }

 printArray(outDataArray, outArrayLength, 2);





  myfile.close();
  return 0;
}