#define BUFLEN 80
#define KROKI 10

#define OPENR 1   // Otwarcie pliku do odczytu
#define OPENW 2   // Otwarcie pliku do zapisu
#define READ 3    // Odczyt fragmentu pliku
#define CLOSE 4   // Zamkniecie pliku
#define WRITE 5   // Zapis fragmentu pliku
#define OPENDIR 6 // Otworz zdalny katalog
#define READDIR 7 // Czytaj zdalny katalog
#define STOP 10   // Zatrzymanie serwera
#define FINISHED 11   // Koniec przesyłania

#define SIZE 512

typedef struct
{
    int typ;        // typ zlecenia
    int ile;        // liczba bajtow
    int fh;         // uchwyt pliku
    char buf[SIZE]; // bufor
} mms_t;

#define PORT 9950

void blad(char *s)
{
    perror(s);
    _exit(1);
}