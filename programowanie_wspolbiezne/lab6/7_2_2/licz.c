#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>

#include "common.h"

// Funkcja zwraca 1 gdy n jest liczbą pierwsza, 0 gdy nie
int pierwsza(int n)
{
    int i, j = 0;
    for (i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return (0);
    }
    return (1);
}

void main(int argc, char **argv)
{
    unsigned int prior = 10;

    // otworzenie kolejki wejsciowej
    mqd_t mqInput = mq_open(INPUT_QUEUE_NAME, O_RDWR, 0660, NULL);
    if (mqInput == -1)
    {
        perror("Kolejka ");
        exit(0);
    }

    // otworzenie kolejki wyjsciowej
    mqd_t mqOutput = mq_open(OUTPUT_QUEUE_NAME, O_RDWR, 0660, NULL);
    if (mqOutput == -1)
    {
        perror("Kolejka ");
        exit(0);
    }

    do
    {
        // Odczytanie danych do przetworzenia

        struct SectionInput nextQueueEntry;
        int resInput = mq_receive(mqInput, (char *)&nextQueueEntry, sizeof(nextQueueEntry), &prior);
        if (resInput < 0)
            perror("read");

        if (nextQueueEntry.numer == 0 && nextQueueEntry.pocz == 0 && nextQueueEntry.kon == 0)
        {
            break;
        }

        // Zliczanie liczb pierwszych dla podanego zakresu

        int primeNumCounter = 0;

        for (int i = nextQueueEntry.pocz; i <= nextQueueEntry.kon; i++)
        {
            if (pierwsza(i))
            {
                primeNumCounter += 1;
            }
        }

        // Wysłanie wyniku obliczeń do kolejki wyjsciowej
        struct SectionResult wynik;
        wynik.numer = nextQueueEntry.numer;
        wynik.ile = primeNumCounter;

        int resOutput = mq_send(mqOutput, (char *)&wynik, sizeof(wynik), prior);
        if (resOutput < 0)
        {
            perror("writing message");
        }

    } while (1);

    printf("Zakonczenie procesu\n");

    mq_close(mqInput);
    mq_close(mqOutput);

    exit(0);
}