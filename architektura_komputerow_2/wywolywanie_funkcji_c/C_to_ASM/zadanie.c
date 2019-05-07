#include <stdio.h>

extern int zmiennaX = 2608;

// funkcja ma być wywołana z poziomu ASM
int sumuj(int a, int b, int c)
{
    printf("A: %d, B: %d, C: %d \n", a, b, c);
    int wynik = a + b + c;

    return wynik;
}

void wyswietl()
{
    printf("zmiennaX: %d \n", zmiennaX);
}