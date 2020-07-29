#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "common.h"

int main(int argc, char *argv[])
{
    // Pobranie argumentów --------------------------
    if (argc < 3)
    {
        printf("Uzycie: cons numer liczba_krokow\n");
        exit(0);
    }
    int num = atoi(argv[1]);
    int steps = atoi(argv[2]);

    int fd = shm_open("bufor", O_RDWR, 0774);
    if (fd == -1)
    {
        perror("open");
        _exit(-1);
    }
    printf("fd: %d\n", fd);

    bufor_t *wbuf = (bufor_t *)mmap(0, sizeof(bufor_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < 10; i++)
    {
        printf("Konsument - cnt: %d odebrano %s\n", wbuf->cnt, wbuf->buf[wbuf->tail]);
        sem_wait(&(wbuf->full));
        sem_wait(&(wbuf->mutex));
        wbuf->cnt--;
        wbuf->tail = (wbuf->tail + 1) % BSIZE;
        sem_post(&(wbuf->mutex));
        sem_post(&(wbuf->empty));
        sleep(1);
    }

    return 0;
}