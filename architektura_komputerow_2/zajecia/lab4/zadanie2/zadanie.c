#include <stdio.h>

extern void round_down();
extern void round_up();
extern void to_nearest();

int main()
{
    printf("1/3: \n");
    round_up();
    printf("Zaokraglenie w gore: %f \n", 1.0f / 3.0f);
    round_down();
    printf("Zaokraglenie w dol: %f \n", 1.0f / 3.0f);
    to_nearest();
    printf("Symetrycznie do parzystej: %f \n", 1.0f / 3.0f);

    printf("2/3: \n");
    round_up();
    printf("Zaokraglenie w gore: %f \n", 2.0f / 3.0f);
    round_down();
    printf("Zaokraglenie w dol: %f \n", 2.0f / 3.0f);
    to_nearest();
    printf("Symetrycznie do parzystej: %f \n", 2.0f / 3.0f);
}