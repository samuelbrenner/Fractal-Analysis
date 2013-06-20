#include <iostream>

 int main(){
 	static int HEIGHT = 5;
 	static int WIDTH = 5;
	int elements[HEIGHT][WIDTH];
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			elements[i][j] = i * j;
		}		
	}
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			printf("%3d", elements[i][j]);
			if(j == 4)
				printf("\n");
		}		
	}
	return 0;
}