#include <semaphore.h>

#define BSIZE 4  // Rozmiar bufora
#define LSIZE 80 //  Dlugosc linii

typedef struct
{
    char buf[BSIZE][LSIZE];
    int head;
    int tail;
    int cnt;
    sem_t mutex;
    sem_t empty;
    sem_t full;
} bufor_t;