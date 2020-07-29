#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

void rec_func()
{
    long x = 1;
    rec_func();
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Za malo argumentow\n");
        return 1;
    }

    int option = atoi(argv[1]);
    int res, i, num = 0;
    struct rlimit rl;

    if (option == 1)
    {
        // Czas zuzycia procesora
        // ulimit -t 2

        printf("\tCUR\tMAX \n");
        getrlimit(RLIMIT_CPU, &rl);
        printf("CPU\t%d\t%d \n", rl.rlim_cur, rl.rlim_max);

        while (1)
            ;
    }
    else if (option == 2)
    {
        // Wielkość pamięci zajmowanej przez stos
        // ulimit -s 10

        printf("\tCUR\tSTACK \n");
        getrlimit(RLIMIT_STACK, &rl);
        printf("CPU\t%d\t%d \n", rl.rlim_cur, rl.rlim_max);

        //long buf[10000];
        rec_func();
    }
    else if (option == 3)
    {
        // Wielkość pamięci zajmowanej przez dane zainicjowane, niezainicjowane i stertę
        // ulimit -d 100

        printf("\tCUR\tDATA \n");
        getrlimit(RLIMIT_DATA, &rl);
        printf("CPU\t%d\t%d \n", rl.rlim_cur, rl.rlim_max);

        long buf[10000];
    }
    else if (option == 4)
    {
        // Maksymalna wielkość pliku utworzonego przez proces
        // ulimit -f 100

        printf("\tCUR\tFSIZE \n");
        getrlimit(RLIMIT_FSIZE, &rl);
        printf("CPU\t%d\t%d \n", rl.rlim_cur, rl.rlim_max);

        FILE *fp;
        fp = fopen("./build/file_name.txt", "w");

        for (int i = 0; i < 10000; i++)
        {
            // dopisz litere do pliku
            if (fputc('d', fp) != 'd')
            {
                printf("Problem z zapisem do pliku");
                break;
            }
        }

        fclose(fp);
    }
    else if (option == 5)
    {
        // Maksymalna ilość plików utworzonych przez proces
        // ulimit -n 9

        printf("\tCUR\tNOFILE \n");
        getrlimit(RLIMIT_NOFILE, &rl);
        printf("CPU\t%d\t%d \n", rl.rlim_cur, rl.rlim_max);

        FILE *files[10];
        for (int x = 0; x < 10; x++)
        {
            char fileNameBuffer[32];
            sprintf(fileNameBuffer, "./build/file_name%d.txt", x);

            files[x] = fopen(fileNameBuffer, "w");

            if (files[x] == NULL)
            {
                printf("Plik nie zostal utworzony");
            }
        }

        for (int x = 0; x < 10; x++)
        {
            fclose(files[x]);
        }
    }
    else if (option == 6)
    {
        // Maksymalna liczba procesów utworzonych przez proces
        // ulimit -u 10

        printf("\tCUR\tNPROC \n");
        getrlimit(RLIMIT_NPROC, &rl);
        printf("CPU\t%d\t%d \n", rl.rlim_cur, rl.rlim_max);

        for (int i = 0; i < 9; i++)
        {
            fork();
        }
    }

    return 0;
}