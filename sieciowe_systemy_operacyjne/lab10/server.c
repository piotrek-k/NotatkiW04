#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <stdbool.h>

#define DEFAULT_PORT 8000
#define MAX_NUMBER_OF_CLIENTS 10

int clientsFds[MAX_NUMBER_OF_CLIENTS];
int registeredClients = 0;

int listeningSocketDesc = 0;
int globalUdpSocket = 0;

struct UdpClient
{
    bool active;
    struct sockaddr_in address;
    socklen_t addrLen;
} knownUdpClients[MAX_NUMBER_OF_CLIENTS];

void broadcast_to_udp_clients(int id_of_client_to_exclude, char *message);
void broadcast_to_tcp_clients(int id_of_client_to_exclude, char *message);

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

void end_connection_udp(int index)
{
    printf("Klient UDP %d kończy połączenie\n", index);
    memset(&knownUdpClients[index], 0, sizeof(knownUdpClients[index]));
}

void handle_udp_message(int sourceOfMessage, char *message)
{
    if (strncmp(message, "quit", strlen("quit")) == 0)
    {
        end_connection_udp(sourceOfMessage);
    }
    else
    {
        // prześlij do innych
        char modifiedMessage[sizeof(message) + 20];
        sprintf(modifiedMessage, "[Klient udp_%d pisze] \n %s", sourceOfMessage, message);

        broadcast_to_udp_clients(sourceOfMessage, modifiedMessage);
        broadcast_to_tcp_clients(-1, modifiedMessage);
    }
}

// id_of_client_to_exclude == -1: prześlij do wszystkich
void broadcast_to_udp_clients(int id_of_client_to_exclude, char *message)
{
    for (int j = 0; j < MAX_NUMBER_OF_CLIENTS; j++)
    {
        if (id_of_client_to_exclude == j || !knownUdpClients[j].active)
        {
            continue;
        }

        int sentBytes = sendto(globalUdpSocket, message, strlen(message) + 1, 0, (struct sockaddr *)&knownUdpClients[j].address, knownUdpClients[j].addrLen);
        if (sentBytes != strlen(message) + 1)
        {
            perror("Błąd wysyłania danych UDP");
        }
    }
}

void handle_tcp_massage(int sourceOfMessage, char *message)
{
    if (strncmp(message, "quit", strlen("quit")) == 0)
    {
        end_connection(sourceOfMessage);
    }

    char modifiedMessage[sizeof(message) + 20];
    sprintf(modifiedMessage, "[Klient tcp_%d pisze] \n %s", sourceOfMessage, message);

    broadcast_to_tcp_clients(sourceOfMessage, modifiedMessage);
    broadcast_to_udp_clients(-1, modifiedMessage);
}

// id_of_client_to_exclude == -1: prześlij do wszystkich
void broadcast_to_tcp_clients(int id_of_client_to_exclude, char *message)
{
    for (int d = 0; d < MAX_NUMBER_OF_CLIENTS; d++)
    {
        if (clientsFds[d] == -1 || (id_of_client_to_exclude != -1 && clientsFds[d] == id_of_client_to_exclude))
        {
            continue;
        }

        int sentBytes = write(clientsFds[d], &message, sizeof(message));
        if (sentBytes < 0)
        {
            perror("write");
        }
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

    // TCP

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

    // UDP
    socklen_t clientAddressLen;
    struct sockaddr_in addressOfClient;

    if ((globalUdpSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        perror("server: nie można utworzyć gniazdka UDP");

    if (bind(globalUdpSocket, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
        perror("serwer: nie można nadać gniazdku lokalnego adresu");

    clientAddressLen = sizeof(addressOfClient);

    int newSocketDesc;
    int numOfReceivedBytes;
    socklen_t clen;
    char message[100];
    struct sockaddr_in cl_addr;
    //struct timeval waitValue;
    fd_set readFds;

    int max = listeningSocketDesc + 1;
    if (max <= globalUdpSocket)
    {
        max = globalUdpSocket + 1;
    }

    memset(&clientsFds, -1, sizeof(clientsFds));
    memset(&knownUdpClients, 0, sizeof(knownUdpClients));

    do
    {
        memset(&message, 0, sizeof(message));

        // waitValue.tv_sec = 5;
        // waitValue.tv_usec = 0;

        FD_ZERO(&readFds);
        FD_SET(listeningSocketDesc, &readFds);
        FD_SET(globalUdpSocket, &readFds);
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
                // nowy klient TCP

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
            else if (FD_ISSET(globalUdpSocket, &readFds))
            {
                // wiadomość przychodząca jako pakiet UDP

                int numOfBytes = recvfrom(globalUdpSocket, message, sizeof(message), 0, (struct sockaddr *)&addressOfClient, &clientAddressLen);

                if (numOfBytes < 0)
                {
                    perror("udp recvfrom error");
                }
                else
                {
                    printf("Received %s\n", message);

                    bool foundSource = false;
                    for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; i++)
                    {
                        if (knownUdpClients[i].address.sin_addr.s_addr == addressOfClient.sin_addr.s_addr &&
                            knownUdpClients[i].address.sin_port == addressOfClient.sin_port)
                        {
                            handle_udp_message(i, message);

                            foundSource = true;
                        }
                    }

                    if (!foundSource)
                    {
                        printf("Wykryto nowego klienta\n");

                        bool foundSlot = false;
                        for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; i++)
                        {
                            if (knownUdpClients[i].active)
                            {
                                continue;
                            }
                            else
                            {
                                knownUdpClients[i].active = true;
                                knownUdpClients[i].address = addressOfClient;
                                knownUdpClients[i].addrLen = sizeof(addressOfClient);

                                handle_udp_message(i, message);

                                foundSlot = true;

                                break;
                            }
                        }

                        if (!foundSlot)
                        {
                            printf("Klient nie mógł zostać zapisany, brak wolnych slotów\n");
                        }
                    }
                }
            }
            else
            {
                // wiadomosci TCP
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

                            handle_tcp_massage(i, message);
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