
.text
.global atoi
.type atoi, @function

atoi:
	push %ebp
	mov %esp, %ebp
	push %ebx

	movl 8(%ebp), %esi 	# adres char
	movl 12(%ebp), %ecx 	# ilosc cyfr
	movl $0, %eax		# rax - rezultat

	add_number:
	movl $8, %edi
	mul %edi		# przesuniecie przecinka
	mov $0, %ebx
	movb (%esi), %bl	# ascii w rbx
	subl $48, %ebx		# konwersja do liczby
	addl %ebx, %eax
	inc %esi
 	loop add_number

	pop %ebx
	movl %ebp, %esp
	pop %ebp

	ret
