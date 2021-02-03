#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

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
    do
    {
        memset(&message, 0, sizeof(message));

        fgets(message, 100, stdin);

        // wysyłanie wiadomości z wejścia
        int sentBytes = write(sock, &message, sizeof(message));
        printf("sent bytes %d\n", sentBytes);

        // komenda quit
        if (strncmp(message, "quit", strlen("quit")) == 0)
        {
            printf("Zatrzymanie klienta...\n");
            shutdown(sock, SHUT_WR);
        }

        // odebranie wiadomości z serwera
        printf("oczekiwanie na wiadomosc z serwera...\n");
        rcvBytes = read(sock, &message, sizeof(message));
        printf("Odebrano: %s\n", message);

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