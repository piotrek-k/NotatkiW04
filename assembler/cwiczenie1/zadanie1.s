# Treść:
# Pobrać ze standardowego strumienia wejściowego procesu ciąg znaków
# i zamienić wszystkie małe litery na wielkie, wszystkie wielkie na
# małe, zmienić wielkość co drugiej litery itp.

SYSCALL32 = 0x80 # wywołanie funkcji standardowej
EXIT = 1 # nr funkcji restartu (=1) – zwrot sterowania do s.o.
EXIT_SUCCESS = 0
STDIN = 0 # nr wejścia standardowego (klawiatura) do %ebx
READ = 3 # nr funkcji odczytu wejścia (=3)
STDOUT = 1 # nr wyjścia standardowego (ekran tekstowy) do %ebx
WRITE = 4 # nr funkcji wyjścia (=4)
ERR_CODE = 0
BUF_SIZE = 10 # rozmiar bufora (1 linia tekstu)

.data
    buf: .ascii ".........\n" # bufor do przechowywania wprowadzonego tekstu
    letterCount: .long 0 # licznik kolejnych liter

    askToEnter: .ascii "Enter text: \n"
    lenAskToEnter = . - askToEnter
    youveEntered: .ascii "You've entered: \n"
    lenYouveEntered = . - youveEntered
    modResultMsg: .ascii "Modified text: \n"
    lenModResultMsg = . - modResultMsg

.text
    .global _start

_start:

    # wypisz na ekranie wiadomość do użytkownika
    mov $WRITE, %eax
    mov $STDOUT, %ebx
    mov $askToEnter, %ecx
    mov $lenAskToEnter, %edx

    int $SYSCALL32

    # wczytanie dziesięciu bajtów
    mov $READ, %eax
    mov $STDIN, %ebx
    mov $buf, %ecx
    mov $BUF_SIZE, %edx

    int $SYSCALL32

    # wypisz na ekranie wiadomość do użytkownika
    mov $WRITE, %eax
    mov $STDOUT, %ebx
    mov $youveEntered, %ecx
    mov $lenYouveEntered, %edx

    int $SYSCALL32

    # wyświetlenie wczytanego tekstu
    mov $WRITE, %eax
    mov $STDOUT, %ebx
    mov $buf, %ecx
    mov $BUF_SIZE, %edx

    int $SYSCALL32

    # wypisz na ekranie wiadomość do użytkownika
    mov $WRITE, %eax
    mov $STDOUT, %ebx
    mov $modResultMsg, %ecx
    mov $lenModResultMsg, %edx

    int $SYSCALL32

    jmp _checkParityModifyThanIncrement

# modyfikuj co drugą literę
_checkParityModifyThanIncrement:
    # oblicz modulo letterCount%2
    movl $0, %edx
    movl letterCount, %eax
    mov $2, %ebx
    divl %ebx # modulo zapisane do edx

    # powiększ letterCount i zapisz do pamięci
    movl letterCount, %eax
    inc %eax
    movl %eax, letterCount

    # jeśli letterCount parzyste, powiększ literę
    mov $0, %eax
    cmp %edx, %eax
    jz _modifyToUppercase

    # jeśli letterCount doszło do 10, zakończ program
    movl letterCount, %eax
    cmpl $10, %eax
    jg _exit

    # przejdź do następnej iteracji
    jmp _checkParityModifyThanIncrement

_modifyToUppercase:
    # pobierz literę z miejsca letterCount
    movl letterCount, %edx
    movl $0, %eax
    movb buf(,%edx,1), %al

    # pomiń poniższe instrukcje, jeśli dane w buforze nie są małą literą
    cmpb $97, %al
    jl _checkParityModifyThanIncrement
    cmpb $122, %al
    jg _checkParityModifyThanIncrement

    # dodaj 32 do wartości litery
    mov $32, %bl
    sub %bl, %al # suma w eax
    movb %al, buf(,%edx,1)
    jmp _checkParityModifyThanIncrement

_exit:
    # wyświetlenie wczytanego tekstu
    mov $WRITE, %eax
    mov $STDOUT, %ebx
    mov $buf, %ecx
    mov $BUF_SIZE, %edx

    int $SYSCALL32

    # zakończenie wykonywania programu
    mov $EXIT, %eax 
    mov $EXIT_SUCCESS, %ebx

    int $SYSCALL32
