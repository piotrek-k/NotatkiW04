#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int id, i;
    for (i = 1; i <= 10; i++)
    {
        printf("Potomny krok: %d \n", i);
        sleep(1);
    }
    exit(i);
}