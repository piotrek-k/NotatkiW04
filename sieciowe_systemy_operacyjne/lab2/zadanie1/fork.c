#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int pid;
    if ((pid = fork()) < 0)
    {
        printf("Blad\n");
    }
    else if (pid == 0)
    {
        /* Proces potomny */
        printf("Potomny: %d\n", getpid());
        exit(0);
    }

    /* Proces macierzysty */
    printf("Macierzysty: %d\n", getpid());
}