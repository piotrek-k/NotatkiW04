#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h> 
#include <math.h>

// funkcja wait
#include <sys/types.h>
#include <sys/wait.h>

extern int errno;

int main(int argc, char **argv)
{
    if (argc <= 3)
    {
        printf("Za mala ilosc argumentow\n");
        return 1;
    }

    long zd = atol(argv[1]);
    long zg = atol(argv[2]);
    int numOfProcesses = atoi(argv[3]);
    long partSize = round((zg-zd+1)/(double)numOfProcesses);
    //printf("partsize %ld\n", partSize);

    //time_t startTime = time(NULL);

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
            long localLowerBound = i*partSize+zd;
            long localUpperBound = (i+1)*partSize+zd;

            char localLowerBoundBuffer[32];
            char localUpperBoundBuffer[32];
            char processNumberBuffer[32];

            sprintf(localLowerBoundBuffer, "%ld", localLowerBound);
            sprintf(localUpperBoundBuffer, "%ld", localUpperBound);
            sprintf(processNumberBuffer, "%ld", i);

            //printf("%ld %ld \n", localLowerBound, localUpperBound);

            int err = execl("./build/licz", "licz", localLowerBoundBuffer, localUpperBoundBuffer, processNumberBuffer, (char *)0);
            if (err == -1)
            {
                fprintf(stderr, "Value of errno: %d\n", errno);
                exit(1);
            }
            exit(0);
        }
    }

    /* Proces macierzysty */

    int pid, status;
    while (numOfProcesses > 0)
    {
        pid = wait(&status);
        //printf("Proces %ld zakonczony ze statusem %d\n", pid, WEXITSTATUS(status));
        numOfProcesses--;
    }


    //time_t timeOfExecution = time(NULL) - startTime;

    //printf("Czas wykonania: %ld \n", timeOfExecution);

    return 0;
}