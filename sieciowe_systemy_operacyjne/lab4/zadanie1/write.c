#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    // otworzenie pliku FIFO
    int fdes = open("./build/FIFO", O_RDWR);
    if (fdes < 0)
    {
        perror("write.c FIFO error");
    }

    char dane[10] = {1};

    for (int i = 0; i < 10000; i++)
    {
        int res = write(fdes, &dane, sizeof(dane));
        if (res < 0)
        {
            perror("writing message");
        }

        if (i % 10 == 0)
        {
            printf("%d\n", i);
        }
    }
    printf("\n");

    close(fdes);

    exit(0);
}