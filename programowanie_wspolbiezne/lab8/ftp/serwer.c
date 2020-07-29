#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>

#include "common.h"

int main(int argc, char *argv[])
{
    mms_t msg;
    struct sockaddr_in adr_moj, adr_cli;
    int s, rec, snd, blen = sizeof(msg), slen = sizeof(adr_moj);

    // Utworzenie i rejestracja nazwy -----------------
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0)
        perror("socket");

    // Ustalenie adresu gniazdka serwera
    memset((char *)&adr_moj, 0, sizeof(adr_moj));
    adr_moj.sin_family = AF_INET;
    adr_moj.sin_port = htons(PORT);
    adr_moj.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *)&adr_moj, sizeof(adr_moj)) == -1)
        perror("bind");

    /*
     * Upewnienie sie ze folder docelowy istnieje
     */

    struct stat st = {0};
    if (stat("./incoming_server", &st) == -1)
    {
        mkdir("./incoming_server", 0700);
    }

    do
    {
        // Odbior polecenia --------------
        rec = recvfrom(s, &msg, blen, 0, (struct sockaddr *)&adr_cli, &slen);
        if (rec < 0)
            blad("recvfrom()");
        printf("Odebrano komunikat %d\n", msg.typ);
        // Dekodowanie polecenia i realizacja
        switch (msg.typ)
        {
        case OPENR:
            printf("Odebrana nazwa pliku: %s\n", msg.buf);

            msg.fh = open(msg.buf, O_RDONLY);
            if (msg.fh < 0)
                perror("open");
            break;
        case READ:
            msg.ile = read(msg.fh, msg.buf, SIZE);
            break;
        case CLOSE:
            if (close(msg.fh) < 0)
            {
                perror("close");
            }
            break;
        case OPENW:
        {
            char newFileName[80];
            strcpy(newFileName, "./incoming_server/\0");
            strcat(newFileName, msg.buf);
            printf("Odebrana nazwa pliku: %s\n", newFileName);

            mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
            int fd = creat(newFileName, mode);
            printf("fd: %d\n", fd);
            if (fd < 0)
            {
                blad("creat");
            }

            msg.fh = open(newFileName, O_WRONLY);
            if (msg.fh < 0)
                perror("open");
            break;
        }
        case WRITE:
        {
            int numWritten = write(msg.fh, msg.buf, msg.ile);
            if (numWritten < 0)
            {
                perror("write");
            }
            break;
        }
        case OPENDIR:
        {
            int r = chdir(msg.buf);
            if (r < 0)
            {
                perror("chdir");
            }
            printf("Zmiana katalogu glownego na %s\n", msg.buf);
            break;
        }
        case READDIR:
        {
            DIR *d;
            struct dirent *dir;
            d = opendir(".");
            if (d)
            {
                while ((dir = readdir(d)) != NULL)
                {
                    //printf("%s\n", dir->d_name);
                    //msg.buf = dir->d_name;
                    strcpy(msg.buf, dir->d_name);
                    snd = sendto(s, &msg, blen, 0, (struct sockaddr *)&adr_cli, slen);
                }
                closedir(d);
                msg.typ = FINISHED;
            }
            break;
        }
        }
        // Wyslanie odpowiedzi ---------
        snd = sendto(s, &msg, blen, 0, (struct sockaddr *)&adr_cli, slen);
        if (snd < 0)
            perror("sendto");
    } while (msg.typ != STOP);
}