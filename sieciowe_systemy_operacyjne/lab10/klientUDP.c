#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define DEFAULT_SERVER_ADDR "127.0.0.1"
#define DEFAULT_PORT 8000

int main(int argc, char *argv[])
{
    char *serv_ip;
    int port;

    if (argc >= 3)
    {
        serv_ip = argv[1];
        sscanf(argv[2], "%d", &port);
    }
    else
    {
        serv_ip = DEFAULT_SERVER_ADDR;
        port = DEFAULT_PORT;
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        perror("socket error");

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(serv_ip);
    servaddr.sin_port = htons(port);

    struct sockaddr_in clientaddr;
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    clientaddr.sin_port = htons(0);

    if (bind(sock, (struct sockaddr *)&clientaddr, sizeof(clientaddr)) < 0)
        perror("klient: nie można nadać gniazdku lokalnego adresu");

    int rcvBytes;
    char message[100];
    int max = 0;
    fd_set readFds;
    do
    {
        memset(&message, 0, sizeof(message));

        FD_ZERO(&readFds);
        FD_SET(0, &readFds);
        FD_SET(sock, &readFds);

        max = sock + 1;

        int activeDesc = select(max, &readFds, NULL, NULL, NULL); //&waitValue

        if (activeDesc > 0)
        {
            if (FD_ISSET(0, &readFds))
            {
                // dane od użytkownika

                rcvBytes = read(0, &message, sizeof(message));

                for (int i = rcvBytes - 1; i >= 0; i--)
                {
                    if (message[i] == '\n' || message[i] == '\r')
                    {
                        message[i] = 0;
                    }
                }

                // wysyłanie wiadomości z wejścia
                int sentBytes = sendto(sock, message, strlen(message), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
                if (sentBytes != strlen(message))
                {
                    perror("Problem z wysłaniem wiadomości\n");
                }

                // komenda quit
                if (strncmp(message, "quit", strlen("quit")) == 0)
                {
                    printf("Zatrzymanie klienta...\n");
                    close(sock);
                    exit(0);
                }
            }
            else if (FD_ISSET(sock, &readFds))
            {
                // dane z serwera

                rcvBytes = read(sock, &message, sizeof(message));
                printf("%s\n", message);
            }
        }

    } while (1);
}