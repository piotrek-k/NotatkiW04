#include <stdio.h>

extern unsigned int measure_register_op();
extern unsigned int measure_memory_read();
extern unsigned int measure_read_os_function();
extern unsigned int measure_scanf_os_function();

int main(void)
{
    //unsigned int register_operation_time = ;

    for (int a = 0; a < 3; a++)
    {
        printf("=======================\n");
        printf("Czas wykonania operacji na rejestrze: %u cykli \n", measure_register_op());
        printf("Czas wykonania operacji na pamieci  : %u cykli \n", measure_memory_read());
        printf("Czas wykonania funkcji read         : %u cykli \n", measure_read_os_function());
        printf("Czas wykonania funkcji scanf        : %u cykli \n", measure_scanf_os_function());
    }

    return 0;
}