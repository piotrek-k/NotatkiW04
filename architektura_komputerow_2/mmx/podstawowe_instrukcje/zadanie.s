.text
.globl copy_memory8, simple_addition, example_of_conversion_and_shift
.type  copy_memory8, @function
.type simple_addition, @function
.type example_of_conversion_and_shift, @function
copy_memory8:
	pushl %ebp
	mov  %esp, %ebp 		# inicjalizacja stosu
	mov 8(%ebp), %eax		# 1. paramter do EAX 

	movq (%eax), %mm0		# pamięć pod adresem w EAX do MM0
	mov 12(%ebp), %eax		# 2. paramter do EAX
	movq %mm0, (%eax)		# zawartość MM0 do EAX

	popl %ebp
	emms
	ret
# .size copy_memory8,.-copy_memory8

simple_addition:
	pushl %ebp
	mov %esp, %ebp

	mov 8(%ebp), %eax
	movq (%eax), %mm0
	mov 12(%ebp), %eax
	movq (%eax), %mm1
	
	paddb %mm0, %mm1
	movq %mm1, (%eax)

	popl %ebp
	emms
	ret

example_of_conversion_and_shift:
	pushl %ebp
	mov %esp, %ebp

	mov 8(%ebp), %eax
	movq (%eax), %mm0
	mov 12(%ebp), %eax
	movq (%eax), %mm1

	# wartości w mm0 i mm2 traktuje jak słowa (2 bajty) i ucina do welkosci 1 bajta
	# zapisuje całość do mm2
	packsswb %mm0, %mm2

	# przesuniecie zawartosci mm1 o 3 bity w lewo (w kierunku bardziej znaczących)
	psllw $3, %mm1

	popl %ebp
	emms
	ret		
