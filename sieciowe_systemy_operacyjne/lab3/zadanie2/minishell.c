#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>
extern int errno;

typedef struct
{
    pthread_cond_t cond1;
    pthread_mutex_t lock;
} shared_data;
static shared_data *data = NULL;

/*
    Tworzy pamięć dzieloną
    Konieczne żeby procesy mogły korzystać z tego samego mutexa
*/
void shared_mem()
{
    char name[16];
    strcpy(name, "Bufor");
    shm_unlink(name);
    int fd;
    if ((fd = shm_open(name, O_RDWR | O_CREAT, 0664)) == -1)
    {
        perror("shm_open");
        exit(-1);
    }

    // place our shared data in shared memory
    int prot = PROT_READ | PROT_WRITE;
    int flags = MAP_SHARED;
    data = mmap(NULL, sizeof(shared_data), prot, flags, fd, 0);
    if (data == NULL)
    {
        perror("mmap");
        exit(-1);
    }

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&data->lock, &attr);

    pthread_cond_init(&data->cond1, NULL);
}

/* 
    Wywołuje podaną komendę, przekierwouje podany deskryptor do jej wejścia.
    Przekazuje numer wyjściowego deskryptora komendy do outputFd
*/
void executeCommand(char *command, char *args, int inputFd, int *outputFd)
{
    pthread_mutex_lock(&data->lock);

    int err = dup2(inputFd, 0);
    if (err == -1)
    {
        perror("dup2 [0] error");
        exit(1);
    }

    *outputFd = dup(1);
    if (*outputFd == -1)
    {
        perror("outputFd [1] error");
        exit(1);
    }

    // deskryptor wyjściowy utworzony, można odblokować rodzica
    pthread_cond_signal(&data->cond1);
    pthread_mutex_unlock(&data->lock);

    err = execlp(command, command, args, NULL);
    if (err == -1)
    {
        perror("execl error");
        exit(1);
    }
}

int main(int argc, char **argv)
{
    char *currentCommand = NULL;
    char *currentArgs = NULL;

    shared_mem();

    int currentFdOut = dup(0);
    int outputFdOfChildProcess = dup(1);

    for (int x = 1; x < argc; x++)
    {
        if (strcmp(argv[x], "+") == 0 || x == argc - 1)
        {
            // 

            printf("nowa komenda\n");

            int pid;
            if ((pid = fork()) < 0)
            {
                perror("Fork error:");
            }
            else if (pid == 0)
            {
                /* Proces potomny */
                printf("Potomny %s: %d\n", currentCommand, getpid());

                executeCommand(currentCommand, currentArgs, currentFdOut, &outputFdOfChildProcess);
            }

            pthread_mutex_lock(&data->lock);
            // czekaj, aż proces potomny utworzy deskrytor wyjściowy
            pthread_cond_wait(&data->cond1, &data->lock);

            printf("%s czyta z %d pisze do %d, address: %p\n", currentCommand, currentFdOut, outputFdOfChildProcess, &outputFdOfChildProcess);
            currentFdOut = outputFdOfChildProcess;

            pthread_mutex_unlock(&data->lock);

            currentCommand = NULL;
            currentArgs = NULL;
        }
        else if (currentCommand == NULL)
        {
            printf("wywolaj %s\n", argv[x]);
            currentCommand = argv[x];
        }
        else
        {
            printf("z argumentami %s\n", argv[x]);

            currentArgs = argv[x];
        }
    }

    exit(0);
}
