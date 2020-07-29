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

struct Result
{
    int pocz; // początek przedzialu
    int kon;  // koniec przedzialu
    int ile;  // Ile liczb w przedziale
};

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

int main(int argc, char **argv)
{
    if (argc <= 3)
    {
        printf("Za mala ilosc argumentow\n");
        return 1;
    }

    long zd = atol(argv[1]);                                       // dolny zakres
    long zg = atol(argv[2]);                                       // gorny zakres
    int numOfProcesses = atoi(argv[3]);                            // liczba procesow
    long partSize = round((zg - zd + 1) / (double)numOfProcesses); // liczb do sprawdzenia na proces

    int fd[2];
    pipe(fd); // utworzenie łącza

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
            close(fd[0]); // zamknięcie strumienia do czytania

            struct Result r;
            r.pocz = i * partSize + zd;
            r.kon = (i + 1) * partSize + zd;
            r.ile = 0;

            // printf("PROC. POT: pocz: %d, kon: %d, ile: %d \n", r.pocz, r.kon, r.ile);

            for (int i = r.pocz; i <= r.kon; i++)
            {
                if (pierwsza(i))
                {
                    r.ile += 1;
                }
            }

            write(fd[1], &r, sizeof(r));

            close(fd[1]); // zamknięcie strumienia do zapisu

            exit(0);
        }
    }

    /* Proces macierzysty */

    // Oczekiwanie na zakończenie wszystkich procesów potomnych
    int pid, status;
    int processCounter = numOfProcesses;
    while (processCounter > 0)
    {
        pid = wait(&status);
        processCounter--;
    }

    struct Result r;
    close(fd[1]);
    for (int n = 0; n < numOfProcesses; n++)
    {
        int rd = read(fd[0], &r, sizeof(r));
        if(rd == -1){
            perror("read");
        }
        printf("pocz: %d, kon: %d, ile: %d \n", r.pocz, r.kon, r.ile);
    }
    close(fd[0]);

    return 0;
}