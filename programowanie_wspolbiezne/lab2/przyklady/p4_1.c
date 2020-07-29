#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// https://stackoverflow.com/questions/16056693/error-when-using-wait-and-fork-in-c
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int pid, status, i;
    if ((pid = fork()) == 0)
    {
        /* Proces potomny ---*/
        for (i = 0; i < 10; i++)
        {
            printf(" Potomny krok: %d\n", i);
            sleep(1);
        }
        exit(0);
    }
    /* Proces macierzysty */
    printf("Macierzysty = %d \n", getpid());
    pid = wait(&status);
    printf("Proces %d zakonczony status: %d\n", pid, WEXITSTATUS(status));
}