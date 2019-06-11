#include <stdio.h>

extern unsigned int measure_independent_op();
extern unsigned int measure_dependent_op();

int main(void)
{
    //unsigned int register_operation_time = ;

    for (int a = 0; a < 10; a++)
    {
        printf("=======================\n");
        printf("Czas wykonania niezaleznych operacji: %u cykli \n", measure_independent_op());
        printf("Czas wykonania zaleznych operacji   : %u cykli \n", measure_dependent_op());
    }

    return 0;
}