#include <stdio.h>

extern unsigned int atoi(char* address, long int size);
//extern unsigned int measure_dependent_op();

char* osemkowa = "1234567";

int main(void){
	long wynik = atoi(osemkowa, 7);
	printf("Wynik: %lu", wynik);
	return 0;
}
