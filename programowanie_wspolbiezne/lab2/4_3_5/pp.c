#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Nieprawidlowa ilosc argumentow\n");
    }
    int numberOfProcess = atoi(argv[1]);
    int steps = atoi(argv[2]);

    for (int i = 1; i <= steps; i++)
    {
        printf("Proces %d krok %d \n", numberOfProcess, i);
        sleep(1);
    }

    exit(numberOfProcess);
}