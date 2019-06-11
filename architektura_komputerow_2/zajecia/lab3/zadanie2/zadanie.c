#include <stdio.h>

extern unsigned long long int count();
//extern unsigned int check_time(unsigned long long prevtime);

int main(void)
{
	unsigned long long int ilosc = 0;

	for (int a = 0; a < 10; a++)
	{
		printf(".");
		ilosc = count();
		printf("Zmierzona wartosc: %llu \n", ilosc);
	}

	return 0;
}