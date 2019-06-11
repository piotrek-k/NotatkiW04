SYSCALL32 = 0x80 # wywołanie funkcji standardowej
EXIT = 1 # nr funkcji restartu (=1) – zwrot sterowania do s.o.
EXIT_SUCCESS = 0
.bss
	.comm short, 2
	.comm char, 1

.data
	msg_short: .asciz "Podaj wartosc short:"			 # ciąg znaków kończący się znakiem \0
	msg_char: .asciz "Podaj wartosc char:"
	formatshort: .asciz "%hu" 					# format danych; oczekuj unsigned short int
	formatchar: .asciz "%s"						# format danych; oczekuj char*
	# %hh dla unsigned char
	breakline: .ascii "\n"

.text
.global main

# .extern printf

main:
	
	push %ebp
	movl %esp, %ebp

	# wiadomosc do uzytkownika
	push $msg_short					# przekazanie adresu początku msg_short (?)
	call printf
	pop %eax

	# pobranie short ze scanf
	mov $0, %eax
	push $short					# parametr: adres do `short`
	push $formatshort				# paramter: adres do początku formatshort (?)
	call scanf
	pop %eax
	pop %eax

	# wyświetlenie short
	mov $0, %eax
	push short					# parametr: wartość z `short`. `short` ma 16 bitów, mieści się na stosie (?)
	push $formatshort				# paramter: adres do początku formatshort (?)
	call printf
	pop %eax
	pop %eax

	# breakline
	push $breakline
	call printf
	addl $4, %esp

	# TEST:  wyświetlenie short GDYBY PODAĆ adres ($)
	mov $0, %eax
	push $short	
	push $formatshort
	call printf
	pop %eax
	pop %eax

	# breakline
	push $breakline
	call printf
	addl $4, %esp

	# wiadomosc do uzytkownika
	push $msg_char
	call printf
	pop %eax

	# pobranie char ze scanf
	mov $0, %eax
	push $char					# parametr: adres do `char`
	push $formatchar
	call scanf
	pop %eax
	pop %eax

	# wyświetlenie char
	mov $0, %eax
	push $char					# parametr: adres do `char`
	push $formatchar
	call printf
	pop %eax
	pop %eax

	# breakline
	push $breakline
	call printf
	addl $4, %esp

	movl %ebp, %esp
	pop %ebp

	ret

mov $EXIT, %eax 
mov $EXIT_SUCCESS, %ebx

int $SYSCALL32
