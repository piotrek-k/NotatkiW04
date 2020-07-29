#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// funkcja wait
#include <sys/types.h>
#include <sys/wait.h>

extern int errno;

int main(int argc, char **argv)
{
    if (argc <= 2)
    {
        printf("Za mala ilosc argumentow\n");
        return 1;
    }

    int numOfChildProcesses = argc - 2;
    int parentProcessStepsCount = atoi(argv[1]);

    for (int i = 2; i < argc; i++)
    {
        char buffer[4];
        snprintf(buffer, sizeof(buffer), "%d", i - 1);

        char command[100];
        memset(command, 0, 100);
        strcat(command, "./build/pp ");
        strcat(command, buffer);
        strcat(command, " ");
        strcat(command, argv[i]);
        int result = system(command);
    }
    
    for (int i = 1; i <= parentProcessStepsCount; i++)
    {
        printf("Proces macierzysty krok %d \n", i);
        sleep(1);
    }

    return 0;
}