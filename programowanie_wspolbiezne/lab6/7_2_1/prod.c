#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 80
#define MQ_NAME "/Kolejka"
#include "common.h"
#define PROD 1

int main(int argc, char *argv[])
{
    int i, res, num, steps = 0;
    unsigned int prior = 10;
    mqd_t mq;
    struct mq_attr attr;
    
    // Pobranie argumentów --------------------------
    if (argc < 3)
    {
        printf("Uzycie: mq_send numer liczba_krokow\n");
        exit(0);
    }
    num = atoi(argv[1]);
    steps = atoi(argv[2]);
    
    // Utworzenie kolejki komunikatow ----------------
    mq = mq_open(MQ_NAME, O_RDWR, 0660, NULL);
    if (mq == -1)
    {
        perror("Kolejka ");
        exit(0);
    }
    printf("Kolejka: %s otwarta, mq: %d\n", MQ_NAME, mq);

    // Wysłanie komunikatów ---------------------------
    for (i = 0; i < 10; i++)
    {
        ms_type msg;
        mq_getattr(mq, &attr);
        printf("W kolejce %ld komunikatow\n", attr.mq_curmsgs);
        printf("Proces %d komunikat %d\n", num, i);
        msg.pnr = num;
        msg.type = PROD;
        strcpy(msg.text, "TEST");
        res = mq_send(mq, (char *)&msg, sizeof(msg), prior);
        if (res == -1)
        {
            perror("Blad zapisu do mq");
            continue;
        }
        printf("Producent %d krok %d \n", num, i);
        sleep(1);
    }
    mq_close(mq);
    mq_unlink(MQ_NAME);

    return 0;
}
