// Producent / konsument  proces odbierajacy komunikaty z kolejki
// Kompilacja gcc mq_rcv.c -o mq_rcv -lrt
#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 80
#define MQ_NAME "/Kolejka"
#include "common.h"

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
    mq = mq_open(MQ_NAME, O_RDWR, 0660, NULL); // | O_CREAT,

    if (mq == -1)
    {
        perror("Kolejka ");
        exit(0);
    }
    printf("Kolejka: %s otwarta, mq: %d\n", MQ_NAME, mq);

    for (i = 0; i < 10; i++)
    {
        ms_type msg;
        mq_getattr(mq, &attr); //  Status kolejki
        printf("W kolejce %ld komunikatow\n", attr.mq_curmsgs);
        res = mq_receive(mq, (char *)&msg, sizeof(msg), &prior);
        if (res == -1)
            perror("Blad odczytu z mq");
        else
            printf("Konsument: %d odebral: %s\n", num, msg.text);
        sleep(1);
    }
    mq_close(mq);
    mq_unlink(MQ_NAME);

    return 0;
}
