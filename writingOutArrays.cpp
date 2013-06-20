#include <fstream>
using namespace std;

int main () {
 static int HEIGHT = 5;
 static int WIDTH = 6;
 ofstream myfile;
 myfile.open ("example.txt");
 
 myfile << HEIGHT;
 myfile << "\n"; 
 myfile << WIDTH; 
 myfile << "\n";

 

 int** elements;
 elements = new int*[HEIGHT];
 


 for(int i = 0; i < HEIGHT; i ++){
 	elements[i] = new int[WIDTH];
 }

 for(int i = 0; i < HEIGHT; i++){
	for(int j = 0; j < WIDTH; j++){
		elements[i][j] = i * j;
	}		
 }

 for(int i = 0; i < HEIGHT; i++){
	for(int j = 0; j < WIDTH; j++){
		printf("%3d", elements[i][j]);
		myfile << elements[i][j];
		myfile << " ";
			if(j == 5){
				printf("\n");
				myfile << "\n";
			}


				
	}
 }

  
  
  myfile.close();
  return 0;
}