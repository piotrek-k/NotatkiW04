SYSCALL32 = 0x80 # wywołanie funkcji standardowej
EXIT = 1 # nr funkcji restartu (=1) – zwrot sterowania do s.o.
EXIT_SUCCESS = 0
STDIN = 0 # nr wejścia standardowego (klawiatura) do %ebx
READ = 3 # nr funkcji odczytu wejścia (=3)
STDOUT = 1 # nr wyjścia standardowego (ekran tekstowy) do %ebx
WRITE = 4 # nr funkcji wyjścia (=4)
ERR_CODE = 0
BUF_SIZE = 131072 # ilość bajtów

.data
	buf: .space BUF_SIZE, 0xff # bufor przechowujacy wynik algorytmu
.text
    .global _start

_start:
	# zaczynam od 2; indeksy 0 i 1 powinny mieć wartosc "1"
	mov $2, %rbx # liczba dla której sprawdzam wielokrotnosci
	mov $2, %rax # indeksy poszczegolnych wielokrotnosci
	
	_nextmultiple:
		add %rbx, %rax # kolejna wielokrotnosc

		# cmpl size_of_data, %eax # czy przekroczono podaną wielkość?
		# jge _nextvalue # skok gdy $BUF_SIZE <= %eax
		cmpq $BUF_SIZE*8, %rax # czy przekroczono zakres bufora?
		jge _nextvalue # skok gdy $BUF_SIZE <= %eax

		btrq %rax, buf # zamien 1 na 0 na pozycji o indeksie eax
		
		jmp _nextmultiple

	_nextvalue:
		inc %rbx # zwieksz wartość sprawdzanej liczby
		mov %rbx, %rax
		cmpq $BUF_SIZE*8, %rbx  # sprawdź czy zwiekszona wartość nie wychodzi poza zakres
		jge _exit
		# cmpl size_of_data, %ebx
		# jge _exit

		jmp _nextmultiple # sprawdz następną wielkokrotność

_exit:

 	# zwróć dane z bufora
    mov $WRITE, %eax
    mov $STDOUT, %ebx
    mov $buf, %ecx
	mov $BUF_SIZE, %rdx
	int $SYSCALL32

	# zakończenie wykonywania programu
    mov $EXIT, %eax 
    mov $EXIT_SUCCESS, %ebx

int $SYSCALL32
