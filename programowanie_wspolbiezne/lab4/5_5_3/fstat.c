#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Nieprawidlowa liczba argumentow");
        exit(1);
    }

    struct stat fileStat;

    int file = open(argv[1], O_RDONLY);
    int res = fstat(file, &fileStat);

    printf("Plik: %s \n", argv[1]);
    printf("Wielkosc: %d b \n", fileStat.st_size);
    printf("Liczba linkow: %d \n", fileStat.st_nlink);
    
    printf("pozwolenia: ");
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    struct stat fileLStat;

    if (lstat(argv[1], &fileLStat) < 0) { 
        perror("calling stat()");
        exit(1);
    }

    printf("Link symboliczny: %s \n", (S_ISLNK(fileLStat.st_mode)) ? "TAK" : "NIE");
}