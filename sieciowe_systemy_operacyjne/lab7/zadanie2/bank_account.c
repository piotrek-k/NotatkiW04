// usleep
#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_OF_THREADS 5
#define MAX_RAND_TIME 200
#define MIN_WAITING_TIME 200
pthread_t tid[NUM_OF_THREADS];
int wynik[NUM_OF_THREADS];

//int balance = 0; // saldo rachunku

const int ENABLE_LOCK = 1; // 0 - aby wyłączyć

typedef struct
{
    int value_of_sem;
    pthread_mutex_t mod_of_sem;
    pthread_cond_t wait_for_sem;
    int balance;
    int id;
} account;

#define NUM_OF_ACCOUNTS 2
account accounts[NUM_OF_ACCOUNTS];

int sem_two_accounts_access = 0;
pthread_mutex_t sem_two_accounts = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait_for_two_accounts = PTHREAD_COND_INITIALIZER;

void take_semaphore_for_two_accounts()
{
    pthread_mutex_lock(&sem_two_accounts);
    while (sem_two_accounts_access > 0)
    {
        pthread_cond_wait(&wait_for_two_accounts, &sem_two_accounts);
    }
    sem_two_accounts_access++;
    pthread_mutex_unlock(&sem_two_accounts);
}

void leave_semaphore_for_two_accounts()
{
    pthread_mutex_lock(&sem_two_accounts);
    sem_two_accounts_access --;
    pthread_cond_signal(&wait_for_two_accounts);
    pthread_mutex_unlock(&sem_two_accounts);
}

void modify_balance(account *acc, int change, int threadId)
{
    int current_balance = acc->balance;

    // przerwa losowej długosci
    int r = rand() % MAX_RAND_TIME;
    usleep(1000 * (MIN_WAITING_TIME + r));

    // modyfikacja
    acc->balance = current_balance + change;
    printf("Wątek %d zmienia stan konta o id %d o %d zł (stan konta %d zł)\n", threadId, acc->id, change, acc->balance);
}

void take_semaphore(account *acc)
{
    pthread_mutex_lock(&acc->mod_of_sem);
    while (acc->value_of_sem > 0)
    {
        pthread_cond_wait(&acc->wait_for_sem, &acc->mod_of_sem);
    }
    acc->value_of_sem++;
    pthread_mutex_unlock(&acc->mod_of_sem);
}

void leave_semaphore(account *acc)
{
    pthread_mutex_lock(&acc->mod_of_sem);
    acc->value_of_sem--;
    pthread_cond_signal(&acc->wait_for_sem);
    pthread_mutex_unlock(&acc->mod_of_sem);
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
        account *acc1 = &accounts[x % 2];
        account *acc2 = &accounts[(x + 1) % 2];

        if (ENABLE_LOCK == 1)
        {
            take_semaphore_for_two_accounts();
            printf("Wątek %d uzyskuje dostep do semafora dla konta 1 lub 2\n", id);

            take_semaphore(acc1);
            printf("Wątek %d uzyskuje dostep do konta o id %d\n", id, acc1->id);
            take_semaphore(acc2);
            printf("Wątek %d uzyskuje dostep do konta o id %d (i ma dostep do dwoch kont)\n", id, acc2->id);

            leave_semaphore_for_two_accounts();
        }

        modify_balance(acc1, -cash_amount, id);
        modify_balance(acc2, +cash_amount, id);

        modify_balance(acc2, -cash_amount, id);
        modify_balance(acc1, +cash_amount, id);

        if (ENABLE_LOCK == 1)
        {
            printf("Wątek %d odblokowuje konta\n", id);
            leave_semaphore(acc2);
            leave_semaphore(acc1);
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

    for (int x = 0; x < NUM_OF_ACCOUNTS; x++)
    {
        // inicjalizacja konta bankowego

        accounts[x].id = x;
        pthread_mutex_init(&accounts[x].mod_of_sem, NULL);
        // ?? nie da się przypisać PTHREAD_COND_INITIALIZER do zmiennej poniżej
        //accounts[x].wait_for_sem = PTHREAD_COND_INITIALIZER;
        accounts[x].balance = 0;
        accounts[x].value_of_sem = 0;
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

    for (int x = 0; x < NUM_OF_ACCOUNTS; x++)
    {
        printf("Stan konta %d: %d zł (oczekiwana wartosc: 0 zł)\n", accounts[x].id, accounts[x].balance);
    }
}