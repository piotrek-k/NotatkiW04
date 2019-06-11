
SYSCALL32 = 0x80 # wywołanie funkcji standardowej
EXIT = 1 # nr funkcji restartu (=1) – zwrot sterowania do s.o.
EXIT_SUCCESS = 0
STDIN = 0 # nr wejścia standardowego (klawiatura) do %ebx
READ = 3 # nr funkcji odczytu wejścia (=3)
STDOUT = 1 # nr wyjścia standardowego (ekran tekstowy) do %ebx
WRITE = 4 # nr funkcji wyjścia (=4)
ERR_CODE = 0
BUF_SIZE = 1 # rozmiar bufora

SHIFT_SIZE = 3 # o ile przesunąć wartości liter

.bss
	.comm buf, BUF_SIZE

.text
    .global _start

_start:

_loadLetter:
 	# wczytanie jednego bajtu
    mov $READ, %eax
    mov $STDIN, %ebx
    mov $buf, %ecx
    mov $BUF_SIZE, %edx
	int $SYSCALL32

	cmp $1, %al
	# oczekuj jednego znaku, wyjdź jeśli będzie inna ilość
	jb _exit

	movb buf, %al # kod ascii litery w rejestrze a

	cmpb $'A', %al
	jl _printAndProceed # nieprawidłowa wartość
	cmpb $'Z', %al
	jg _printAndProceed # nieprawidłowa wartość
	
	# buf powinien być w prawidłowym zakresie

	add $SHIFT_SIZE, %al # zwiekszenie kodu ascii o SHIFT_SIZE

	cmpb $'Z', %al
	jg _letterOutOfRange # 'Z' > %al
	jle _printAndProceed # 'Z' <= %al
	
_letterOutOfRange:
	# po zwiększeniu o 3 wartości, przekroczono wartość
	# ascii litery 'Z'

	sub $'Z', %al # otrzymujemy wartość o 1 za dużą
	dec %al
	add $'A', %al

	# upewnienie się, że już jesteśmy w zakresie
	cmp $'Z', %al
	jg _letterOutOfRange

_printAndProceed:
	movb %al, buf

	# wyświetlenie wczytanego tekstu
	mov $WRITE, %eax
	mov $STDOUT, %ebx
	mov $buf, %ecx
	mov $BUF_SIZE, %edx
	int $SYSCALL32

	jmp _loadLetter # czytaj dalej

_exit:

	# zakończenie wykonywania programu
    mov $EXIT, %eax 
    mov $EXIT_SUCCESS, %ebx

	int $SYSCALL32
