#include <stdio.h>

extern unsigned long long myTimer();
extern int addThreeNumbers(int a, int b, int c);

int main(void)
{
    unsigned long long actualTime = myTimer();

    printf("Od uruchomienia komputera wykonało się %llu cykli procesora.\n", actualTime);

    printf("addThreeNumbers %d \n", addThreeNumbers(1, 2, 3));

    return 0;
}