#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int fd[2];
    pipe(fd); // utworzenie łącza
    int message = 0;

    int pid;
    if ((pid = fork()) < 0)
    {
        printf("Blad\n");
    }
    else if (pid == 0)
    {
        /* Proces potomny */
        printf("Potomny: %d\n", getpid());

        for(int x=0; x<100000; x++)
        {
            int rd = write(fd[1], &message, sizeof(int));
            message ++;
            if (rd == -1)
            {
                perror("write");
            }
        }

        exit(0);
    }

    sleep(1);

    int result = 0;
    int rd;
    while (rd > -1)
    {
        rd = read(fd[0], &result, sizeof(int));
        if (rd == -1)
        {
            perror("read");
        }
        else {
            printf("%d\n", result);
        }
    }

    /* Proces macierzysty */
    printf("Macierzysty: %d\n", getpid());
}