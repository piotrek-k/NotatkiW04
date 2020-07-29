#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <math.h>
#include <semaphore.h>
#include <sys/mman.h>

#include "common.h"

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
        printf("[zakres_dolny][zakres_gorny][liczba_proc]\n");
        return 1;
    }

    long zd = atol(argv[1]);            // dolny zakres
    long zg = atol(argv[2]);            // gorny zakres
    int numOfProcesses = atoi(argv[3]); // liczba procesow
    long partSize = round((zg - zd + 1) / (double)numOfProcesses); // liczb do sprawdzenia na proces

    buf_t *buf;
    
    // Utworzenie segmentu ---------------------------
    shm_unlink("bufor");
    int fd = shm_open("bufor", O_RDWR | O_CREAT, 0774);
    if (fd == -1)
    {
        perror("open");
        _exit(-1);
    }
    printf("fd: %d\n", fd);
    int size = ftruncate(fd, sizeof(buf_t));
    if (size < 0)
    {
        perror("trunc");
        _exit(-1);
    }
    // Odwzorowanie segmentu fd w obszar pamieci procesow
    buf_t *wbuf;
    wbuf = (buf_t *)mmap(0, sizeof(buf_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (wbuf == NULL)
    {
        perror("map");
        _exit(-1);
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

            // Zliczanie liczb pierwszych dla podanego zakresu

            int primeNumCounter = 0;

            for (int i = localLowerBound; i <= localUpperBound; i++)
            {
                if (pierwsza(i))
                {
                    primeNumCounter += 1;
                }
            }

            wbuf->dane[i].pocz = localLowerBound;
            wbuf->dane[i].kon = localUpperBound;
            wbuf->dane[i].suma = primeNumCounter;
            wbuf->wymiar = localUpperBound - localLowerBound;
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

    int overallsum = 0;
    int reports = 0;
    for (int x = 0; x < SIZE; x++)
    {
        printf("Raport %d: suma liczb: %d. Zakres dolny: %d, zakres gorny: %d\n", x, wbuf->dane[x].suma, wbuf->dane[x].pocz, wbuf->dane[x].kon);
        if (wbuf->wymiar > 0)
        {
            overallsum += wbuf->dane[x].suma;
            reports += 1;
        }
    }

    printf("\nIlosc raportow: %d, suma liczb pierwszych: %d\n", reports, overallsum);

    return 0;
}