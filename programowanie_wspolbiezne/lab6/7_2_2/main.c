#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
// funkcja wait
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <math.h>

#include "common.h"

int main(int argc, char **argv)
{
    if (argc <= 4)
    {
        printf("Za mala ilosc argumentow\n");
        printf("[zakres_dolny][zakres_gorny][liczba_proc][dlug_sekcji]\n");
        return 1;
    }

    long zd = atol(argv[1]);            // dolny zakres
    long zg = atol(argv[2]);            // gorny zakres
    int numOfProcesses = atoi(argv[3]); // liczba procesow
    int sectionLength = atoi(argv[4]);  // dlugosc_przedzialu
    int sectionNum = ceil((zg - zd) / (float)sectionLength);

    struct SectionInput inputData;
    struct SectionResult outputData;
    unsigned int prior = 10;

    if (mq_unlink(INPUT_QUEUE_NAME) == 0)
        fprintf(stdout, "Czyszczenie kolejki %s \n", INPUT_QUEUE_NAME);
    if (mq_unlink(OUTPUT_QUEUE_NAME) == 0)
        fprintf(stdout, "Czyszczenie kolejki %s \n", OUTPUT_QUEUE_NAME);

    // Utworzenie kolejek POSIX

    struct mq_attr attr;
    attr.mq_msgsize = sizeof(inputData);
    attr.mq_maxmsg = 4;
    attr.mq_flags = 0;
    mqd_t mqInput = mq_open(INPUT_QUEUE_NAME, O_RDWR | O_CREAT, 0660, &attr);
    if (mqInput == -1)
    {
        perror("Kolejka ");
        exit(0);
    }
    attr.mq_msgsize = sizeof(outputData);
    attr.mq_maxmsg = 4;
    attr.mq_flags = 0;
    mqd_t mqOutput = mq_open(OUTPUT_QUEUE_NAME, O_RDWR | O_CREAT, 0660, &attr);
    if (mqOutput == -1)
    {
        perror("Kolejka ");
        exit(0);
    }

    // Uruchomienie procesów wykonawczych

    for (int i = 0; i < numOfProcesses; i++)
    {
        int pid;
        if ((pid = fork()) < 0)
        {
            printf("Blad przy tworzeniu procesu potomnego\n");
        }
        else if (pid == 0)
        {
            int err = execl("./build/licz", "licz", (char *)0);
            if (err == -1)
            {
                fprintf(stderr, "Value of errno: %d\n", errno);
                exit(1);
            }
            exit(0);
        }
    }

    /* Proces macierzysty */

    // Utworzenie podporcesu dodającego nowe dane do kolejki

    int pidDataAdder;
    if ((pidDataAdder = fork()) < 0)
    {
        printf("Blad przy tworzeniu procesu potomnego\n");
    }
    else if (pidDataAdder == 0)
    {

        int currentStartPoint = zd;
        int currentEndPoint = zd + sectionLength;
        int sectionCounter = 1;

        while (currentEndPoint <= zg)
        {
            inputData.pocz = currentStartPoint;
            inputData.kon = currentEndPoint;
            inputData.numer = sectionCounter;

            int res = mq_send(mqInput, (char *)&inputData, sizeof(inputData), prior);

            currentStartPoint = currentEndPoint;
            currentEndPoint = currentStartPoint + sectionLength;
            if (currentEndPoint > zg)
            {
                currentEndPoint = zg;
            }
            if (currentEndPoint == currentStartPoint)
            {
                break;
            }
            sectionCounter++;
        }

        // Dodanie informacji o końcu napływu danych
        // po jednej dla każdego procesu
        struct SectionInput sec = {0, 0, 0};
        for (int i = 0; i < numOfProcesses + 1; i++)
        {
            int resInput = mq_send(mqInput, (char *)&sec, sizeof(sec), prior);
        }

        exit(0);
    }

    // Odczytanie wyników obliczeń

    int suma_lp = 0;   // suma liczb pierwszych
    int suma_proc = 0; // suma odczytanych raportów
    int resOutput = 0; // wartość z mq_receive

    printf("\nsekcja \t ilosc_liczb_pierwszych\n");
    for (int x = 0; x < sectionNum; x++)
    {
        resOutput = mq_receive(mqOutput, (char *)&outputData, sizeof(outputData), NULL);
        if (resOutput < 0)
            perror("read");

        printf("%d \t %d \n", outputData.numer, outputData.ile);

        suma_proc++;
        suma_lp += outputData.ile;
    }

    mq_close(mqInput);
    mq_close(mqOutput);

    // Oczekiwanie na zakończenie wszystkich procesów potomnych

    int pid, status;
    int processCounter = numOfProcesses;
    while (processCounter > 0)
    {
        pid = wait(&status);
        if (pid < 0)
        {
            break;
        }
        processCounter--;
    }

    printf("\nIlosc raportow: %d, suma liczb pierwszych: %d\n", suma_proc, suma_lp);

    return 0;
}