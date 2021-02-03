#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <termios.h>

static struct termios old, current;

/*
Rozwiązanie problemu odczytywania wartości klawisza zapożyczone z
https://stackoverflow.com/a/7469410/1804027
*/

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old);         /* grab old terminal i/o settings */
    current = old;              /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo)
    {
        current.c_lflag |= ECHO; /* set echo mode */
    }
    else
    {
        current.c_lflag &= ~ECHO; /* set no echo mode */
    }
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void)
{
    return getch_(0);
}

int main(int argc, char **argv)
{
    // utworzenie pliku FIFO
    unlink("./tmp/FIFO");
    if (mkfifo("./tmp/FIFO", 0666) < 0)
    {
        perror("mkfifo");
        return 0;
    }

    // otworzenie pliku FIFO
    int fdes = open("./tmp/FIFO", O_RDWR);
    if (fdes < 0)
    {
        perror("Open");
        exit(1);
    }

    // uruchomienie mplayera
    int pid;
    if ((pid = fork()) < 0)
    {
        printf("Blad przy tworzeniu procesu potomnego\n");
    }
    else if (pid == 0)
    {
        int err = execlp("mplayer", "mplayer", "-slave", "-input", "file=./tmp/FIFO", "file.mp3", (char *)0);
        if (err == -1)
        {
            perror("Execl error");
            exit(1);
        }
        exit(0);
    }

    while (1)
    {
        printf("(getch example) please type a letter...");
        char c = getch();
        printf("\nYou typed: %c\n", c);

        if (c == 'p')
        {
            printf("pausing...\n");
            char command[] = "pause\n";
            int res = write(fdes, &command, sizeof(command));
            if (res < 0)
            {
                perror("writing message");
            }
        }
        else if (c == 's')
        {
            printf("seek 5sec...\n");
            char command[] = "seek 5 0\n";
            int res = write(fdes, &command, sizeof(command));
            if (res < 0)
            {
                perror("writing message");
            }
        }
        else if (c == 'q')
        {
            break;
        }
    }

    resetTermios();
    
    int childStatus;
    wait(&childStatus);
}