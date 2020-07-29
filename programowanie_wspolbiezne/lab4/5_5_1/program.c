// Program do kopiowania plików - funkcje  niskiego poziomu
// argumenty: [path_file1] [path_file2]

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Nieodpowiednia ilosc argumentow (%d)", argc);
        return 1;
    }
    char *file1 = argv[1];
    char *file2 = argv[2];

    char buf[512];

    int res, fd, rd;
    if ((fd = open(file1, O_RDONLY)) == -1)
    {
        perror("open");
        exit(0);
    }

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int fd2 = creat(file2, mode);

    int all_read_bytes = 0;
    do
    {
        rd = read(fd, buf, 512);
        
        if (rd != -1)
        {
            all_read_bytes += write(fd2, buf, rd);
        }
    } while (rd > 0);

    close(fd2);
    close(fd);
    return 0;
}