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

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        perror("socket error");

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(serv_ip);
    sockaddr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        perror("connect error");
        exit(0);
    }

    printf("Połączenie nawiązane\n");

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
                    if(message[i] == '\n' || message[i] == '\r' ){
                        message[i] = 0;
                    }
                }

                // wysyłanie wiadomości z wejścia
                write(sock, &message, sizeof(message) - 1);
                //printf("sent bytes %d\n", sentBytes);

                // komenda quit
                if (strncmp(message, "quit", strlen("quit")) == 0)
                {
                    printf("Zatrzymanie klienta...\n");
                    shutdown(sock, SHUT_WR);
                }
            }
            else if (FD_ISSET(sock, &readFds))
            {
                // dane z serwera

                rcvBytes = read(sock, &message, sizeof(message));
                printf("%s\n", message);
            }
        }

    } while (rcvBytes > 0);

    if (rcvBytes == 0)
    { // EOF
        shutdown(sock, SHUT_RDWR);
        close(sock);
    }
    else
    {
        perror("read");
    }
}