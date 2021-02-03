#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define DEFAULT_PORT 8000
#define MAX_NUMBER_OF_CLIENTS 10

int clientsFds[MAX_NUMBER_OF_CLIENTS];
int registeredClients = 0;

int listeningSocketDesc = 0;

void end_connection(int desc)
{
    printf("Klient kończy połączenie\n");
    shutdown(desc, SHUT_RD);
    close(desc);
    for (int d = 0; d < MAX_NUMBER_OF_CLIENTS; d++)
    {
        if (clientsFds[d] == desc)
        {
            clientsFds[d] = -1;
            break;
        }
    }

    registeredClients--;

    if (registeredClients == 0)
    {
        printf("stopping server...\n");
        shutdown(listeningSocketDesc, SHUT_RD);
        close(listeningSocketDesc);
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    int port;
    if (argc > 1)
    {
        sscanf(argv[1], "%d", &port);
    }
    else
    {
        port = DEFAULT_PORT;
    }

    listeningSocketDesc = socket(AF_INET, SOCK_STREAM, 0);
    if (listeningSocketDesc < 0)
        perror("socket error");

    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(port);

    if (bind(listeningSocketDesc, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
        perror("bind error");

    int listenResult = listen(listeningSocketDesc, 3);
    if (listenResult < 0)
    {
        perror("listen problem");
    }

    int newSocketDesc;
    int numOfReceivedBytes;
    socklen_t clen;
    char message[100];
    struct sockaddr_in cl_addr;
    struct timeval waitValue;
    fd_set readFds;

    int max = listeningSocketDesc + 1;

    memset(&clientsFds, -1, sizeof(clientsFds));

    do
    {
        memset(&message, 0, sizeof(message));

        // waitValue.tv_sec = 5;
        // waitValue.tv_usec = 0;

        FD_ZERO(&readFds);
        FD_SET(listeningSocketDesc, &readFds);
        for (int x = 0; x < MAX_NUMBER_OF_CLIENTS; x++)
        {
            if (clientsFds[x] != -1)
            {
                FD_SET(clientsFds[x], &readFds);
            }
        }

        printf("Oczekiwanie na wiadomosci\n");

        int activeDesc = select(max, &readFds, NULL, NULL, NULL); //&waitValue

        if (activeDesc > 0)
        {
            if (FD_ISSET(listeningSocketDesc, &readFds))
            {
                // nowy klient

                clen = sizeof(cl_addr);
                newSocketDesc = accept(listeningSocketDesc, (struct sockaddr *)&cl_addr, &clen);

                if (newSocketDesc < 0)
                {
                    perror("socket accept error");
                }
                else
                {
                    printf("Dołączono nowego użytkownika\n");

                    int c = 0;
                    while (clientsFds[c] != -1 && c < MAX_NUMBER_OF_CLIENTS)
                    {
                        c++;
                    }

                    if (c == MAX_NUMBER_OF_CLIENTS)
                    {
                        printf("Brak miejsca dla nowych klientow");
                    }
                    else
                    {
                        printf("Wybrano slot %d\n", c);
                        registeredClients++;

                        clientsFds[c] = newSocketDesc;

                        if (max <= newSocketDesc)
                        {
                            max = newSocketDesc + 1;
                        }
                    }
                }
            }
            else
            {
                // wiadomosci
                for (int i = 0; i < max; i++)
                {
                    if (FD_ISSET(i, &readFds))
                    {
                        printf("Deskryptor %d\n", i);

                        numOfReceivedBytes = read(i, &message, sizeof(message));

                        if (numOfReceivedBytes < 0)
                        {
                            perror("receiving error");
                        }
                        else if (numOfReceivedBytes == 0)
                        {
                            end_connection(i);
                            break;
                        }
                        else
                        {
                            printf("Received %s\n", message);

                            if (strncmp(message, "quit", strlen("quit")) == 0)
                            {
                                end_connection(i);
                            }

                            char modifiedMessage[sizeof(message) + 20];
                            sprintf(modifiedMessage, "[Klient %d pisze] \n %s", i, message);

                            for (int d = 0; d < MAX_NUMBER_OF_CLIENTS; d++)
                            {
                                if (clientsFds[d] == -1 || clientsFds[d] == i)
                                {
                                    continue;
                                }

                                int sentBytes = write(clientsFds[d], &modifiedMessage, sizeof(modifiedMessage));
                                if (sentBytes < 0)
                                {
                                    perror("write");
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            perror("select");
        }

    } while (1);
}