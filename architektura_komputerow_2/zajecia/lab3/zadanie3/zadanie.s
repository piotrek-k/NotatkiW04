SYSCALL32 = 0x80 # wywołanie funkcji standardowej
EXIT = 1 # nr funkcji restartu (=1) – zwrot sterowania do s.o.
EXIT_SUCCESS = 0

.data
	format_break_line: .asciz "\n"
	format_int: .asciz "%d"
	format_char_pointer: .asciz "%s"
	format_unsgn_char: .asciz "%hhd"

.extern zmienna_int

.text
.global main

main:
	pushl %ebp
    movl %esp, %ebp

	# wyświetlenie int
	push zmienna_int
	push $format_int
	call printf
	addl $8, %esp

	call breakline

	# wyświetlenie zawartości zmiennej char
	push pointer_to_char
	push $format_char_pointer
	call printf
	addl $8, %esp

	call breakline

	# wyświetlenie całej tablicy

	# mov $0, %ecx

	# continue_printing:
	# cmpl $10, %ecx
	# jg end_printing
	
	# inc %ecx
	# push %ecx
	# leal pointer_to_char(,%ecx,1), %ecx
	# push %ecx
	# push $format_char_pointer
	# call printf
	# addl $8, %esp
	# call breakline
	# pop %ecx
	# jmp continue_printing

	# end_printing:

	mov %ebp, %esp
    popl %ebp

	ret

breakline:
	pushl %ebp
    movl %esp, %ebp
	
	push $format_break_line
	call printf
	addl $4, %esp

	mov %ebp, %esp
    popl %ebp

	ret
# zakończenie wykonywania programu
# mov $EXIT, %eax 
# mov $EXIT_SUCCESS, %ebx

# int $SYSCALL32