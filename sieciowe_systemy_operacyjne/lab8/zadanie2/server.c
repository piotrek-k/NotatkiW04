#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 8000

int main(int argc, char *argv[])
{
    int port;
    if (argc > 1)
    {
        sscanf(argv[1], "%d", &port);
    }
    else {
        port = DEFAULT_PORT;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        perror("socket error");

    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
        perror("bind error");

    int listenResult = listen(sock, 3);
    if (listenResult < 0)
    {
        perror("listen problem");
    }

    int newSocketDesc;
    int numOfReceivedBytes;
    socklen_t clen;
    char message[100];
    struct sockaddr_in cl_addr;
    do
    {
        printf("Oczekiwanie na połączenie\n");
        clen = sizeof(cl_addr);
        newSocketDesc = accept(sock, (struct sockaddr*) &cl_addr, &clen);

        if (newSocketDesc < 0)
        {
            perror("socket accept error");
        }
        else
        {
            printf("Połączenie aktywne\n");

            do
            {
                memset(message, 0, sizeof(message));

                numOfReceivedBytes = read(newSocketDesc, &message, sizeof(message));

                if (numOfReceivedBytes < 0)
                {
                    perror("receiving error");
                }
                else if (numOfReceivedBytes == 0)
                {
                    printf("Koniec połączenia\n");
                    break;
                }
                else
                {
                    printf("Received %s\n", message);

                    if (strncmp(message, "quit", strlen("quit")) == 0)
                    {
                        printf("stopping server...\n");
                        shutdown(newSocketDesc, SHUT_RD);
                        close(newSocketDesc);
                        exit(0);
                    }

                    int sentBytes = write(newSocketDesc, &message, sizeof(message));
                    if(sentBytes < 0){
                        perror("write");
                    }
                }
            } while (1);
        }

    } while (1);
}