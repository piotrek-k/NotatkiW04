#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pierwsza(int n)
// Funkcja zwraca 1 gdy n jest liczbą pierwsza, 0 gdy nie
{
    int i, j = 0;
    for (i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return (0);
    }
    return (1);
}

void main(int argc, char **argv)
{
    if (argc <= 3)
    {
        printf("Nieprawidlowa ilosc argumentow %d \n", argc);
    }
    long lowerBound = atol(argv[1]);
    long upperBound = atol(argv[2]);
    int processNum = atoi(argv[3]);

    int primeNumCounter = 0;

    for (int i = lowerBound; i <= upperBound; i++)
    {
        if (pierwsza(i))
        {
            primeNumCounter += 1;
        }
    }

    exit(primeNumCounter);
}