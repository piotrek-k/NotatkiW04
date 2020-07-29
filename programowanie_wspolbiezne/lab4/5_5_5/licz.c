#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Funkcja zwraca 1 gdy n jest liczbą pierwsza, 0 gdy nie
int pierwsza(int n)
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

    int fd;
    if ((fd = open("wynik.bin", O_WRONLY | O_APPEND)) == -1)
    {
        perror("open");
        printf("Cannot open");
        exit(0);
    }

    int res = lockf(fd, F_LOCK, 0);
    if (res == -1)
    {
        perror("lockf -1");
        exit(1);
    }

    struct Wynik
    {
        int pocz; // początek przedzialu
        int kon;  // koniec przedzialu
        int ile;  // Ile liczb w przedziale
    } wynik;

    wynik.pocz = lowerBound;
    wynik.kon = upperBound;
    wynik.ile = primeNumCounter;

    write(fd, &wynik, sizeof(struct Wynik));

    res = lockf(fd, F_ULOCK, 0);
    if (res == -1)
    {
        perror("lockf -2");
        exit(1);
    }

    close(fd);

    exit(primeNumCounter);
}