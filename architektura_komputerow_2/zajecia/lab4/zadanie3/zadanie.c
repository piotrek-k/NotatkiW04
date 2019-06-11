#include <stdio.h>

extern void enable_32bit_precision();
extern void enable_64bit_precision();
extern void enable_80bit_precision();
extern void put_result_on_stack();

int main()
{
    printf("1/3: \n");
    enable_32bit_precision();
    put_result_on_stack();
    enable_64bit_precision();
    put_result_on_stack();
    enable_80bit_precision();
    put_result_on_stack();
}