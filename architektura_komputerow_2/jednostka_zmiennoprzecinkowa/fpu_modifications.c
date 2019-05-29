#include <stdio.h>

extern void print_control_word_state();
extern void change_control_word_at_positon(int position, int state);
extern int print_state_of_bit_of_control_word(int position);
extern float run_fpu_calculations();

int main()
{
    print_control_word_state();
    printf("Stan bitow 10, 11: %d", print_state_of_bit_of_control_word(10));
    printf("%d\n", print_state_of_bit_of_control_word(11));
    printf("Obliczony float: %f\n", run_fpu_calculations());

    change_control_word_at_positon(10, 0);
    change_control_word_at_positon(11, 1);
    print_control_word_state();
    printf("Stan bitow: 10, 11: %d", print_state_of_bit_of_control_word(10));
    printf("%d\n", print_state_of_bit_of_control_word(11));
    printf("Obliczony float: %f\n", run_fpu_calculations());
}