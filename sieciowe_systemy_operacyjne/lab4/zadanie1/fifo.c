#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    // utworzenie pliku FIFO
    unlink("./build/FIFO");
    if (mkfifo("./build/FIFO", 0666) < 0)
    {
        perror("mkfifo");
        // return 0;
    }

    // czytanie z pliku FIFO
    int fdes = open("./build/FIFO", O_RDWR);
    if (fdes < 0)
    {
        perror("Open");
        exit(1);
    }

    // drugi proces, piszący do FIFO
    int pid;
    if ((pid = fork()) < 0)
    {
        printf("Blad przy tworzeniu procesu potomnego\n");
    }
    else if (pid == 0)
    {
        int err = execl("./build/write.out", "write", (char *)0);
        if (err == -1)
        {
            perror("Execl error");
            exit(1);
        }
        exit(0);
    }

    int childStatus;
    wait(&childStatus);
}