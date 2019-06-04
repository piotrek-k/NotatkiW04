NUM_OF_JUMPS = 8

.text
.global modify_matrix
.type modify_matrix, @function

modify_matrix:
	pushl %ebp
	mov %esp, %ebp
	
	mov 8(%ebp), %eax				# pobranie adresu macierzy
	
	mov $0, %edi
	loop:
	movq (%eax,%edi,8), %mm0 	# przenieś kolejne 64 bity tablicy do mm0
	inc %edi
	movq (%eax,%edi,8), %mm1
	# w rejestrach znajduje się po 8 wartości 8 bitowych
	paddb %mm0, %mm1				# dodaj mm0 do mm1, zapisz w mm1
	movq %mm1, (%eax, %edi, 8) # zapisz wynik w macierzy
	inc %edi
	
	cmp $NUM_OF_JUMPS, %edi
	jl loop

	popl %ebp
	emms
	ret
		
