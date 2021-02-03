// usleep
#define _DEFAULT_SOURCE

#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define SHM_KEY 13102
#define PH_ARRAY_SIZE 5

#define SEM_KEY_BASE 5000
#define SEM_PERM 0666
#define SEM_KEY_TABLE 5100

#define EATING_TIME_MS 3000
#define MEDITATION_TIME_MS 100
#define MAX_RAND_TIME 100

const int ENABLE_PROBLEM_SOLUTION = 1; // 0 - żeby wyłączyć

typedef struct
{
    int ph_counter;
    char all_philosophers_states[PH_ARRAY_SIZE];
    int sem_id;
} shared_data;

int shm_id;

int current_ph_id = 0;
int current_ph_state = 0;

shared_data *data;

int tableSemId = 0;

void request_access_to_table();
void leave_table();
void take_fork(int forkIndex);
void give_back_fork(int forkIndex);

void print_sem(int semid)
{
    printf("semval ");
    for (int x = 0; x < PH_ARRAY_SIZE; x++)
    {
        printf("%d.", semctl(semid, x, GETVAL));
    }
    printf("\n");
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    /**
     *  Inicjalizacja pamięci współdzielonej
     */
    int created = 0;
    shm_id = shmget(SHM_KEY, sizeof(shared_data), IPC_CREAT | IPC_EXCL | 0666);
    if (shm_id < 0)
    {
        // perror("shmget error\n");

        shm_id = shmget(SHM_KEY, sizeof(shared_data), 0666);
        if (shm_id < 0)
        {
            perror("shmget error 2\n");
        }
    }
    else
    {
        created = 1;
    }

    printf("shmid %d\n", shm_id);

    data = (shared_data *)shmat(shm_id, NULL, 0);

    /**
     *  Inicjalizacja semaforów
     */
    int semid;
    if ((semid = semget(SEM_KEY_BASE, PH_ARRAY_SIZE, SEM_PERM | IPC_EXCL | IPC_CREAT)) < 0)
    {
        printf("already created\n");
        semid = semget(SEM_KEY_BASE, PH_ARRAY_SIZE, 0);
        if (semid < 0)
        {
            perror("semget");
            exit(1);
        }
    }
    else
    {
        print_sem(semid);

        struct sembuf sem_buf;
        for (int x = 0; x < PH_ARRAY_SIZE; x++)
        {
            sem_buf.sem_op = 1;
            sem_buf.sem_flg = 0;
            sem_buf.sem_num = x;
            int retval = semop(semid, &sem_buf, 1);
            if (retval == -1)
            {
                perror("semop");
                exit(1);
            }
        }

        print_sem(semid);
    }
    printf("got sem %d\n", semid);
    data->sem_id = semid;

    // semafor pilnujący dostępu do stołu
    if ((tableSemId = semget(SEM_KEY_TABLE, 1, SEM_PERM | IPC_EXCL | IPC_CREAT)) < 0)
    {
        printf("sem_table already created\n");
        tableSemId = semget(SEM_KEY_TABLE, 1, 0);
        if (tableSemId < 0)
        {
            perror("semget");
            exit(1);
        }
    }
    else
    {
        int ret = semctl(tableSemId, 0, SETVAL, PH_ARRAY_SIZE - 1);
        print_sem(tableSemId);
    }
    printf("got table sem %d\n", tableSemId);

    /**
     *  Logika programu
     */

    printf("Id filozofa: %s\n", argv[1]);
    current_ph_id = atoi(argv[1]);

    if (current_ph_id == 0)
    {
        for (int x = 0; x < PH_ARRAY_SIZE; x++)
        {
            data->all_philosophers_states[x] = '.';
        }
    }

    // Wymuszenie wystąpienia zakleszczenia na samym początku działania programu
    usleep(1000 * 500 * current_ph_id);

    data->ph_counter = current_ph_id + 1;

    if (current_ph_id >= PH_ARRAY_SIZE)
    {
        printf("Zbyt duża liczba filozofów\n");
        exit(1);
    }

    printf("[%s] filozof %d  start\n", data->all_philosophers_states, current_ph_id);
    while (1)
    {
        if (current_ph_state == 0)
        {
            request_access_to_table();

            // weź  1. widelec
            take_fork(mod((current_ph_id), PH_ARRAY_SIZE));

            current_ph_state++;
            data->all_philosophers_states[current_ph_id] = '1';

            printf("[%s] filozof %d bierze 1. widelec\n", data->all_philosophers_states, current_ph_id);

            usleep(1000 * 1000 * 4);
        }
        else if (current_ph_state == 1)
        {
            // weź 2. widelec
            take_fork(mod((current_ph_id - 1), PH_ARRAY_SIZE));

            current_ph_state++;
            data->all_philosophers_states[current_ph_id] = '2';

            printf("[%s] filozof %d bierze 2. widelec\n", data->all_philosophers_states, current_ph_id);
        }
        else if (current_ph_state == 2)
        {
            // zacznij jeść
            current_ph_state++;
            data->all_philosophers_states[current_ph_id] = 'j';

            printf("[%s] filozof %d zaczyna jeść\n", data->all_philosophers_states, current_ph_id);

            int r = rand() % MAX_RAND_TIME;
            usleep(1000 * (EATING_TIME_MS + r));

            give_back_fork(mod(current_ph_id - 1, PH_ARRAY_SIZE));
            give_back_fork(mod(current_ph_id, PH_ARRAY_SIZE));

            leave_table();
        }
        else if (current_ph_state == 3)
        {
            // idź medytować
            current_ph_state = 0;
            data->all_philosophers_states[current_ph_id] = 'm';

            printf("[%s] filozof %d zaczyna medytować\n", data->all_philosophers_states, current_ph_id);

            int r = rand() % MAX_RAND_TIME;
            usleep(1000 * (MEDITATION_TIME_MS + r));

            data->all_philosophers_states[current_ph_id] = '.';

            printf("[%s] filozof %d czeka na widelec\n", data->all_philosophers_states, current_ph_id);
        }
    }

    shmdt(data);

    return 0;
}

// limit jedzących: jedno miejsce przy stole zawsze wolne
void request_access_to_table()
{
    if (ENABLE_PROBLEM_SOLUTION == 1)
    {
        printf("[%s] Filozof %d prosi o dostęp do stołu\n", data->all_philosophers_states, current_ph_id);
        // print_sem(tableSemId);

        struct sembuf sops[1];

        sops[0].sem_num = 0;
        sops[0].sem_op = -1; /* Zajęcie semafora */
        sops[0].sem_flg = SEM_UNDO;

        int retval = semop(tableSemId, sops, 1);
        if (retval == -1)
        {
            perror("semop");
            return;
        }

        printf("[%s] Filozof %d uzyskał dostęp do stołu\n", data->all_philosophers_states, current_ph_id);
    }
}

// limit jedzących: jedno miejsce przy stole zawsze wolne
void leave_table()
{
    if (ENABLE_PROBLEM_SOLUTION == 1)
    {
        struct sembuf sops[1];

        sops[0].sem_num = 0;
        sops[0].sem_op = 1; /* Opuszczenie semafora */
        sops[0].sem_flg = SEM_UNDO;

        int retval = semop(tableSemId, sops, 1);
        if (retval == -1)
        {
            perror("semop");
            return;
        }

        printf("Filozof %d opuścił stół\n", current_ph_id);
    }
}

void take_fork(int forkIndex)
{
    //printf("taking %d\n", forkIndex);
    //print_sem(data->sem_id);

    struct sembuf sops[1];

    sops[0].sem_num = forkIndex;
    sops[0].sem_op = -1; /* Zajęcie semafora */
    sops[0].sem_flg = SEM_UNDO;

    int retval = semop(data->sem_id, sops, 1);
    if (retval == -1)
    {
        perror("semop");
        return;
    }

    //printf("tf ");
    //print_sem(data->sem_id);
}

void give_back_fork(int forkIndex)
{
    //printf("giving back %d\n", forkIndex);
    //print_sem(data->sem_id);

    struct sembuf sops[1];

    sops[0].sem_num = forkIndex;
    sops[0].sem_op = 1; /* Opuszczenie semafora */
    sops[0].sem_flg = SEM_UNDO;

    int retval = semop(data->sem_id, sops, 1);
    if (retval == -1)
    {
        perror("semop");
        return;
    }

    //printf("gbf ");
    //print_sem(data->sem_id);
}