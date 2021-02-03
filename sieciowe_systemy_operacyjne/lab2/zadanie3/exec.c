#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <errno.h>
extern int errno;

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
        // do wyjścia łącza
        dup2(fd[1], 1);

        int err = execlp("ls", "ls", "-la", NULL);
        if (err == -1)
        {
            fprintf(stderr, "Value of errno: %d\n", errno);
            exit(1);
        }
    }

    /* Proces macierzysty */
    printf("Macierzysty: %d\n", getpid());

    close(fd[1]);

    char buf[BUFSIZ];
    while (1)
    {
        int numOfBytes = read(fd[0], buf, sizeof(buf));
        if(numOfBytes < 0){
            perror("read");
        }

        if (numOfBytes == 0)
        {
            break;
        }

        // modyfikacja otrzymanych danych
        for (int x = 0; x < strlen(buf); x++)
        {
            if (buf[x] >= 'a' && buf[x] <= 'z')
            {
                buf[x] = buf[x] - 32;
            }
        }

        printf("%s", buf);
    }

    int childStatus;
    wait(&childStatus);
}