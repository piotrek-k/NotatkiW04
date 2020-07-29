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

    long zd = atol(argv[1]);                                       // dolny zakres
    long zg = atol(argv[2]);                                       // gorny zakres
    int numOfProcesses = atoi(argv[3]);                            // liczba procesow
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

    if (sem_init(&(wbuf->allow_post), 1, SIZE))
    {
        perror("full");
        _exit(0);
    }

    if (sem_init(&(wbuf->allow_read), 1, 0))
    {
        perror("allow_read");
        _exit(0);
    }

    if (sem_init(&(wbuf->allow_read_pos_mod), 1, 1))
    {
        perror("allow_read_pos_mod");
        _exit(0);
    }

    wbuf->tail = 0;
    wbuf->head = 0;

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

            sem_wait(&(wbuf->allow_post));
            sem_wait(&(wbuf->allow_read_pos_mod));

            wbuf->head = (wbuf->head + 1) % SIZE;

            printf("Zapis na pozycji %d\n", wbuf->head);

            wbuf->dane[wbuf->head].pocz = localLowerBound;
            wbuf->dane[wbuf->head].kon = localUpperBound;
            wbuf->dane[wbuf->head].suma = primeNumCounter;
            wbuf->wymiar = localUpperBound - localLowerBound;

            sem_post(&(wbuf->allow_read_pos_mod));
            sem_post(&(wbuf->allow_read));

            exit(0);
        }
    }

    /* Proces macierzysty */

    // Odbieranie danych
    int overallsum = 0;
    int reports = 0;
    for (int i = 0; i < numOfProcesses; i++)
    {
        printf("Oczekiwanie na odebranie %d... \n", i);

        sem_wait(&(wbuf->allow_read));
        sem_wait(&(wbuf->allow_read_pos_mod));

        wbuf->tail = (wbuf->tail + 1) % SIZE;

        printf("Odczyt z pozycji %d: suma liczb: %d. Zakres dolny: %d, zakres gorny: %d\n",
               wbuf->tail,
               wbuf->dane[wbuf->tail].suma,
               wbuf->dane[wbuf->tail].pocz,
               wbuf->dane[wbuf->tail].kon);

        if (wbuf->wymiar > 0)
        {
            overallsum += wbuf->dane[wbuf->tail].suma;
            reports += 1;
        }

        sem_post(&(wbuf->allow_read_pos_mod));
        // printf("%d odbiera... \n", i);
        sem_post(&(wbuf->allow_post));
    }

    // Oczekiwanie na zakończenie wszystkich procesów potomnych
    int pid, status;
    while (numOfProcesses > 0)
    {
        pid = wait(&status);
        numOfProcesses--;
    }

    printf("\nIlosc raportow: %d, suma liczb pierwszych: %d\n", reports, overallsum);

    return 0;
}