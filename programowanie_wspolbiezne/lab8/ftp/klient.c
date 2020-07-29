#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "common.h"

int main(int argc, char *argv[])
{
    mms_t msg;
    memset(&msg, 0, sizeof(msg)); // clear struct

    /*
     * Połączenie z serwerem
     */

    struct sockaddr_in adr_moj, adr_cli, adr_serw;
    int s, snd, rec, blen = sizeof(mms_t), slen = sizeof(adr_serw);

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0)
        blad("socket");

    printf("Gniazdko %d utworzone\n", s);
    memset((char *)&adr_serw, 0, sizeof(adr_serw));
    adr_serw.sin_family = AF_INET;
    adr_serw.sin_port = htons(PORT);
    if (inet_aton("127.0.0.1", &adr_serw.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        _exit(1);
    }

    /*
     * Pobranie opcji
     */

    printf("==============\n");
    printf("Wybierz opcję:\n");
    printf("0 - odczyt pliku z serwera\n");
    printf("1 - przeslanie pliku do serwera\n");
    printf("2 - sprawdzenie zawartosci folderu na serwerze\n");
    printf("3 - zmiana katalogu\n");
    printf("==============\n");

    char *input = NULL;
    size_t len = 0;
    printf("Podaj czynnosc: \n");
    getline(&input, &len, stdin);
    int action = input[0] - '0';

    char *fileName = NULL;

    if (action == 0 || action == 1)
    {
        /*
         * Uzytkownik chce transferowac pliki
         */

        do
        {
            //Otwarcie pliku
            printf("Podaj nazwe pliku: ");
            int chars = getline(&fileName, &len, stdin);
            if (fileName[chars - 1] == '\n')
            {
                fileName[chars - 1] = '\0';
                --chars;
            }
            strcpy(msg.buf, fileName);
            strcat(msg.buf, "\0");
            if (action == 0)
            {
                msg.typ = OPENR;
            }
            else
            {
                msg.typ = OPENW;
            }
            snd = sendto(s, &msg, blen, 0, (struct sockaddr *)&adr_serw, slen);
            if (snd < 0)
                perror("sendto()");
            rec = recvfrom(s, &msg, blen, 0, (struct sockaddr *)&adr_moj, &slen);
            if (rec < 0)
                perror("recvfrom()");
        } while (msg.fh < 0);

        if (action == 0)
        {
            /*
             * Upewnienie sie ze folder docelowy istnieje
             */

            struct stat st = {0};
            if (stat("./incoming_client", &st) == -1)
            {
                printf("Tworzenie folderu incoming_client\n");
                mkdir("./incoming_client", 0700);
            }

            /*
             * Utworzenie lokalnego pliku
             */

            mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
            char newFileName[80];
            strcpy(newFileName, "./incoming_client/\0");
            strcat(newFileName, fileName);

            printf("> Klient: tworzenie pliku o nazwie: %s\n", newFileName);
            int fd = creat(newFileName, mode);
            if (fd < 0)
            {
                blad("creat");
            }

            do
            {
                // Odczyt --------------------
                msg.typ = READ;
                msg.ile = SIZE;
                snd = sendto(s, &msg, blen, 0, (struct sockaddr *)&adr_serw, slen);
                if (snd < 0)
                    perror("sendto()");
                rec = recvfrom(s, &msg, blen, 0, (struct sockaddr *)&adr_moj, &slen);
                if (rec < 0)
                    perror("recvfrom()");
                printf("> Odebrano %d bajtow\n", msg.ile);
                if (msg.ile > 0)
                    printf("%s\n", msg.buf);

                // zapis do pliku
                write(fd, msg.buf, msg.ile);

            } while (msg.ile == SIZE);

            // Zamknięcie pliku
            msg.typ = CLOSE;
            snd = sendto(s, &msg, blen, 0, (struct sockaddr *)&adr_serw, slen);
            if (snd < 0)
                perror("sendto()");
        }
        else if (action == 1)
        {

            /*
             * Odczyt z pliku 
             */
            int fd, rd;
            char buf[SIZE];
            if ((fd = open(fileName, O_RDONLY)) == -1)
            {
                perror("open");
            }

            do
            {
                rd = read(fd, &msg.buf, SIZE);

                /**
                 * Wysłanie danych
                 */

                msg.typ = WRITE;
                msg.ile = rd;
                snd = sendto(s, &msg, blen, 0, (struct sockaddr *)&adr_serw, slen);
                if (snd < 0)
                    perror("sendto()");

                printf("> Wyslano %d bajtow\n", msg.ile);

            } while (rd > 0);

            msg.typ = CLOSE;
            snd = sendto(s, &msg, blen, 0, (struct sockaddr *)&adr_serw, slen);
            if (snd < 0)
                perror("sendto()");
        }
    }

    if (action == 2)
    {
        /*
         * READDIR
         */

        msg.typ = READDIR;
        snd = sendto(s, &msg, blen, 0, (struct sockaddr *)&adr_serw, slen);
        if (snd < 0)
            perror("sendto");

        while (msg.typ != FINISHED)
        {
            rec = recvfrom(s, &msg, blen, 0, (struct sockaddr *)&adr_moj, &slen);
            if (rec < 0)
                perror("recvfrom()");
            printf("> %s\n", msg.buf);
        }
    }

    if (action == 3)
    {
        char *dirName = NULL;
        printf("Podaj katalog: ");
        int chars = getline(&dirName, &len, stdin);
        if (dirName[chars - 1] == '\n')
        {
            dirName[chars - 1] = '\0';
            --chars;
        }

        msg.typ = OPENDIR;
        strcpy(msg.buf, dirName);
        snd = sendto(s, &msg, blen, 0, (struct sockaddr *)&adr_serw, slen);
        if (snd < 0)
            perror("sendto");
    }
}