#define SIZE 3

typedef struct
{
    int pocz;
    int kon;
    int suma;
} dane_t;

typedef struct
{
    int wymiar;
    sem_t allow_post;
    sem_t allow_read;
    sem_t allow_read_pos_mod;
    //int read_pos;
    dane_t dane[SIZE];
    int head; // pozycja na którą dopisywane są wyniki
    int tail; // pozycja z ktorej konsument pobiera dane
} buf_t;

extern int errno;