#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{

    for (int x = 1; x <= 32000; x *= 2)
    {
        time_t startTime = time(NULL);
        char buf[80];
        sprintf(buf, "./build/program 1 20000000 %d", x);
        int result = system(buf);

        time_t timeOfExecution = time(NULL) - startTime;

        printf("Czas wykonania dla l.proc.=%d: %ld \n", x, timeOfExecution);
    }
}