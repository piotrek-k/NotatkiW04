#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int fd[2];
    pipe(fd); // utworzenie łącza

    int pid;
    if ((pid = fork()) < 0)
    {
        printf("Blad\n");
    }
    else if (pid == 0)
    {
        /* Proces potomny */
        printf("Potomny: %d\n", getpid());

        // zamknięcie desykryptora odczytu
        close(fd[0]);
        // przekierowanie strumienia wyjściowego 1 (wyjście procesu)
        // do strumienia zapisu łącza
        int err = dup2(fd[1], 1);
        if (err == -1)
        {
            perror("Proc. pot. dup2");
            exit(1);
        }

        err = execlp("cal", "cal", "2020", NULL);
        //err = execl("/bin/ls", "ls", "-la", NULL);
        if (err == -1)
        {
            perror("Proc. pot. execlp");
            exit(1);
        }
    }

    int status;
    wait(&status);

    /* Proces macierzysty */
    printf("Macierzysty: %d\n", getpid());

    close(fd[1]);

    // przekierowanie strumienia wyjściowego 0 (wyjście procesu)
    // do strumienia odczytu łącza
    int err = dup2(fd[0], 0);
    if (err == -1)
    {
        perror("Proc. mac. dup2");
        exit(1);
    }

    err = execl("/bin/tac", "tac", NULL);
    if (err == -1)
    {
        perror("Proc. mac. execl");
        exit(1);
    }
}