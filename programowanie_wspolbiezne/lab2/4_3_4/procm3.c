#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// funkcja wait
#include <sys/types.h>
#include <sys/wait.h>

extern int errno;

int main(int argc, char **argv)
{
    if (argc <= 2)
    {
        printf("Za mala ilosc argumentow\n");
        return 1;
    }

    int numOfChildProcesses = argc - 2;
    int parentProcessStepsCount = atoi(argv[1]);

    for (int i = 2; i < argc; i++)
    {
        // generowanie procesów potomnych
        int pid;
        if ((pid = fork()) < 0)
        {
            printf("Blad przy tworzeniu procesu potomnego\n");
        }
        else if (pid == 0)
        {
            // execl wymaga podania lancucha znakow jako argumentu
            if(i-1 > 9999){
                printf("Blad: za duza liczba");
            }
            char buffer[4];
            snprintf(buffer, sizeof(buffer), "%d", i - 1);

            int err = execl("./build/proc_pot", "proc_pot", buffer, argv[i], NULL);
            if (err == -1)
            {
                fprintf(stderr, "Value of errno: %d\n", errno);
                exit(1);
            }
            exit(0);
        }
    }

    /* Proces macierzysty */
    for (int i = 1; i <= parentProcessStepsCount; i++)
    {
        printf("Proces macierzysty krok %d \n", i);
        sleep(1);
    }

    int pid, status;
    printf("PID procesu macierzystego: %d \n", getpid());
    while (numOfChildProcesses > 0)
    {
        pid = wait(&status);
        printf("Proces %ld zakonczony ze statusem %d\n", pid, WEXITSTATUS(status));
        numOfChildProcesses--;
    }

    return 0;
}