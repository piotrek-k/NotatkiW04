#include <stdio.h>

extern void print_control_word_state();
extern void change_control_word_at_positon(int position, int state);
extern int print_state_of_bit_of_control_word(int position);

int main()
{
    print_control_word_state();
    printf("Stan bitow 9, 10: %d", print_state_of_bit_of_control_word(9));
    printf("%d\n", print_state_of_bit_of_control_word(10));
    change_control_word_at_positon(9, 1);
    change_control_word_at_positon(10, 1);
    print_control_word_state();
    printf("Stan bitow: 9, 10: %d", print_state_of_bit_of_control_word(9));
    printf("%d\n", print_state_of_bit_of_control_word(10));
}