#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define KEY 13000

int shm_id;

int main(int argc, char *argv[])
{
    shm_id = shmget(KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
    if (shm_id < 0)
    {
        // perror("shmget error\n");

        shm_id = shmget(KEY, sizeof(int), 0666);
        if (shm_id < 0)
        {
            perror("shmget error 2\n");
        }
    }
    else {
        // TODO: inicjalizacja pamieci
    }

    int *sharedInteger = (int *)shmat(shm_id, NULL, 0);

    (*sharedInteger)++;

    printf("%d\n", *sharedInteger);

    shmdt(sharedInteger); 

    return 0;
}