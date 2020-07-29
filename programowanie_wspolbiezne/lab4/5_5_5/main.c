#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
// funkcja wait
#include <sys/types.h>
#include <sys/wait.h>

extern int errno;

int main(int argc, char **argv)
{
    if (argc <= 3)
    {
        printf("Za mala ilosc argumentow\n");
        return 1;
    }

    long zd = atol(argv[1]); // dolny zakres
    long zg = atol(argv[2]); // gorny zakres
    int numOfProcesses = atoi(argv[3]); // liczba procesow
    long partSize = round((zg - zd + 1) / (double)numOfProcesses); // liczb do sprawdzenia na proces

    int fd;
    if ((fd = open("wynik.bin", O_CREAT | O_TRUNC | O_RDWR)) == -1)
    {
        perror("open");
        exit(0);
    }

    for (int i = 0; i < numOfProcesses; i++)
    {
        // generowanie procesów potomnych
        int pid;
        if ((pid = fork()) < 0)
        {
            printf("Blad przy tworzeniu procesu potomnego\n");
        }
        else if (pid == 0)
        {
            long localLowerBound = i * partSize + zd;
            long localUpperBound = (i + 1) * partSize + zd;

            char localLowerBoundBuffer[32];
            char localUpperBoundBuffer[32];
            char processNumberBuffer[32];

            sprintf(localLowerBoundBuffer, "%ld", localLowerBound);
            sprintf(localUpperBoundBuffer, "%ld", localUpperBound);
            sprintf(processNumberBuffer, "%ld", i);

            int err = execl("./build/licz", "licz", localLowerBoundBuffer, localUpperBoundBuffer, processNumberBuffer, (char *)0);
            if (err == -1)
            {
                fprintf(stderr, "Value of errno: %d\n", errno);
                exit(1);
            }
            exit(0);
        }
    }

    /* Proces macierzysty */

    // Oczekiwanie na zakończenie wszystkich procesów potomnych
    int pid, status;
    while (numOfProcesses > 0)
    {
        pid = wait(&status);
        numOfProcesses--;
    }

    struct
    {
        int pocz; // początek przedzialu
        int kon;  // koniec przedzialu
        int ile;  // Ile liczb w przedziale
    } wynik;

    int suma_lp = 0;    // suma liczb pierwszych
    int suma_proc = 0;  // suma odczytanych raportów

    while(read(fd, &wynik, sizeof(wynik)))
    {
        suma_proc++;
        suma_lp += wynik.ile;
    }

    printf("Ilosc raportow: %d, ilosc liczb pierwszych: %d\n", suma_proc, suma_lp);

    return 0;
}