# dokumentacja:
# http://www.zak.ict.pwr.wroc.pl/materials/architektura/laboratorium%20AK2/Dokumentacja/Intel%20Penium%20IV/IA-32%20Intel%20Architecture%20Software%20Developers%20Manual%20vol.%201%20-%20Basic%20Architecture.pdf#page=222&zoom=auto,-27,504

.bss
	status_word: .short 0

.text
.global try_dividing_by_zero, make_precision_exception
.type try_dividing_by_zero, @function
.type make_precision_exception, @function


try_dividing_by_zero:
	push    %ebp
	mov %esp, %ebp

	# argument 1. do st(0)
	flds 8(%ebp)

	# dzielenie przez 2. argument
	fdivs 12(%ebp)					# wynik w st(0)
	
	# zapisz w pamieci
	fstps -4(%ebp)

	# wynik na stos w celu zwrocenia wartosci
	flds	-4(%ebp)

	mov     %ebp, %esp
    pop     %ebp
	ret

make_precision_exception:
	push    %ebp
	mov %esp, %ebp
	push %ebx

	movl $0, %ebx
	fstsw status_word
	movw status_word, %bx

	THIRD_STOP:
	# WYŚWIETLIĆ EBX. BIT PIĄTY POWINIEN BYĆ RÓWNY 0

	subl $4, %esp

	# argument 1. do st(0)
	flds 8(%ebp)
	# movl 8(%ebp), %eax

	# oblicz sinus z argumentu w rejestrze st(0)
	fsin
	
	# zapisz st(0) w pamieci (zdejmij ze stosu)
	fstps -8(%ebp)

	# movl -8(%ebp), %eax
	flds	-8(%ebp)			# wynik na stosie

	movl $0, %ebx
	fstsw   status_word
	mov status_word, %bx
	FOURTH_STOP:
	# WYŚWIETLIĆ EBX. BIT PIĄTY POWINIEN BYĆ RÓWNY 1

	addl $4, %esp
	pop %ebx
	mov     %ebp, %esp
    pop     %ebp
	ret

