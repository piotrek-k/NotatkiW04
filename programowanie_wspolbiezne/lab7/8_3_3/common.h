#define INPUT_QUEUE_NAME "/InputQueue"
#define OUTPUT_QUEUE_NAME "/OutputQueue"

#define SIZE 10

typedef struct
{
    int pocz;
    int kon;
    int suma;
} dane_t;

typedef struct
{
    int wymiar;
    dane_t dane[SIZE];
} buf_t;

extern int errno;