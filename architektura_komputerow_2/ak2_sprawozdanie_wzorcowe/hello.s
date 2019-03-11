# proces kompilacji zautomatyzowany plikiem Makefile:
# $ make
# uruchomienie programu:
# $ gdb [name]
# (gdb) run


SYSEXIT = 1
SYSREAD = 3
SYSWRITE = 4
STDOUT = 1
EXIT_SUCCESS = 0

# Zmusza kompilator do wyrównania kodu programu do granicy
# słowa maszynowego, co ma wpływ na zwiększenie szybkości
# wymiany danych między procesorem a pamięcią operacyjną
.align 32

.text
msg_hello: .ascii "Hello, world!\n"
# Obliczenie długości ciągu znaków. '.' oznacza bieżącą pozycję,
# 'msg_hello' to pozycja początkowa ciągu znaków. Różnica tych wartości
# równa jest długości ciągu.
msg_hello_len = . - msg_hello

.global _start # wskazanie punktu wejścia programu

_start:
    # chcemy wywołać funkcję systemową platformy Linux/x86
    # w tym celu należy odpowiednio ustawić wartości rejestrów
    # eax - numer funkcji, ebx, ecx, ...; - argumenty
    # 0x80 - przerwanie programowe
    mov $SYSWRITE, %eax # wstawienie wartości funkcji systemowej SYSWRITE do %eax
    mov $STDOUT, %ebx # 1 arg. - syst. deskryptor stdout
    mov $msg_hello, %ecx # 2 arg. - adres początkowy napisu
    mov $msg_hello_len, %edx # 3 arg. - długość łańcucha

    int $0x80 # wywołanie funkcji systemowej

    # następna funkcja systemu do wywołania to SYSEXIT
    mov $SYSEXIT, %eax 
    mov $EXIT_SUCCESS, %ebx

    int $0x80