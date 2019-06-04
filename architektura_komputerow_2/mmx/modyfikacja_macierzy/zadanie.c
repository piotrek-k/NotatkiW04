#include <stdio.h>

#define MATRIX_SIZE 8
#define NUM_OF_JUMPS ((MATRIX_SIZE/8)/2*MATRIX_SIZE)

char matrix[MATRIX_SIZE][MATRIX_SIZE];

void modify_matrix(char * matrix);

int main(){
	for(int a=0; a<MATRIX_SIZE; a++){
		for(int b=0; b<MATRIX_SIZE; b++){
			matrix[a][b] = a+1;
			printf("%hhx", matrix[a][b]);		
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");
	modify_matrix(*matrix);

	for(int a=0; a<MATRIX_SIZE; a++){
		for(int b=0; b<MATRIX_SIZE; b++){
			printf("%hhx", matrix[a][b]);		
		}
		printf("\n");
	}

}
