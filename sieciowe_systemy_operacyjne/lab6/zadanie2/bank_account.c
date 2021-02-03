// usleep
#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_OF_THREADS 5
#define MAX_RAND_TIME 2000
#define MIN_WAITING_TIME 500
pthread_t tid[NUM_OF_THREADS];
int wynik[NUM_OF_THREADS];

int balance = 0; // saldo rachunku

const int ENABLE_LOCK = 0; // 0 - aby wyłączyć

sem_t mutex;

void *thread(void *arg)
{
    int id = *((int *)arg);
    printf("Start wątku %d\n", id);

    int cash_amount = 100;
    if (id % 2)
    {
        cash_amount = 50;
    }

    for (int x = 0; x < 3; x++)
    {
        if (ENABLE_LOCK == 1)
        {
            sem_wait(&mutex);
        }

        int current_balance = balance;

        // wpłacenie
        balance = current_balance + cash_amount;
        printf("Wątek %d wpłaca %d (stan konta %d)\n", id, cash_amount, balance);

        current_balance = balance;

        // przerwa losowej długosci
        int r = rand() % MAX_RAND_TIME;
        usleep(1000 * (MIN_WAITING_TIME + r));

        // wypłacenie

        balance = current_balance - cash_amount;
        printf("Wątek %d wypłacił %d  (stan konta %d)\n", id, cash_amount, balance);

        if (ENABLE_LOCK == 1)
        {
            sem_post(&mutex);
        }
    }

    printf("Koniec wątku %d\n", id);

    wynik[id] = id;
    free(arg);
    pthread_exit((void *)&wynik[id]);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    void **statp;

    if (sem_init(&mutex, 1, 1))
    {
        perror("mutex");
        exit(1);
    }

    for (int i = 0; i < NUM_OF_THREADS; i++)
    {
        int *arg = malloc(sizeof(*arg));
        *arg = i + 1;
        pthread_create(&tid[i], NULL, thread, arg);
    }
    for (int i = 0; i < NUM_OF_THREADS; i++)
    {
        pthread_join(tid[i], (void *)&statp);
        printf("Watek %d zakonczony\n", (int)*statp);
    }

    printf("Stan konta: %d (oczekiwana wartosc: 0)\n", balance);
}