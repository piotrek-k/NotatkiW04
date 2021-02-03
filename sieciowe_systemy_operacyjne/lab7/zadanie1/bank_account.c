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

const int ENABLE_LOCK = 1; // 0 - aby wyłączyć

int value_of_sem = 0;
pthread_mutex_t mod_of_sem = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait_for_sem = PTHREAD_COND_INITIALIZER;

void take_semaphore()
{
    pthread_mutex_lock(&mod_of_sem);
    while (value_of_sem > 0)
    {
        pthread_cond_wait(&wait_for_sem, &mod_of_sem);
    }
    value_of_sem++;
    pthread_mutex_unlock(&mod_of_sem);
}

void leave_semaphore()
{
    pthread_mutex_lock(&mod_of_sem);
    value_of_sem --;
    pthread_cond_broadcast(&wait_for_sem);
    pthread_mutex_unlock(&mod_of_sem);
}

void *thread(void *arg)
{
    //printf("ENABLE_LOCK %d\n", ENABLE_LOCK);
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
            printf("Wątek %d wnioskuje o dostep\n", id);
            take_semaphore();
            printf("Wątek %d uzyskuje dostep\n", id);
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
            leave_semaphore();
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

    pthread_mutex_init(&mod_of_sem, NULL);

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