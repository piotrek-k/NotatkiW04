#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#define MQ_NAME "/Kolejka"

#include <errno.h>
extern int errno;

#include "common.h"

int main(int argc, char *argv[])
{

    // Pobranie argumentów --------------------------
    if (argc < 2)
    {
        printf("Argumenty: [wielkosc_kolejki]\n");
        exit(0);
    }
    int queueSize = atoi(argv[1]);

    struct mq_attr attr;
    mqd_t mq;
    attr.mq_msgsize = sizeof(ms_type);
    attr.mq_maxmsg = queueSize;
    attr.mq_flags = 0;
    mq = mq_open(MQ_NAME, O_RDWR | O_CREAT, 0660, &attr);

    return 0;
}