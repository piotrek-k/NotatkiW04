	.file	"fpu.c"
	.text
	.globl	getFPUreturnFPU
	.type	getFPUreturnFPU, @function
getFPUreturnFPU:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	# POWIĘKSZ STOS O 16, PRZECHOWANIE LOKALNEJ ZMIENNEJ FLOAT
	subl	$16, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	# KOPIUJ ARGUMENT 1 DO REJESTRU ST
	flds	8(%ebp)
	# PODZIEL ZAWARTOŚĆ ST(0) PRZEZ LICZBĘ POD WSKAZANYM ADRESEM
	fdivs	12(%ebp)
	# ZDEJMIJ ST(0) ZE STOSU FPU, ZAPISZ W ZAREZERWOWANEJ PAMIĘCI
	fstps	-4(%ebp)
	# KOPIUJ Z PODANEJ PAMIĘCI DO ST(0)???
	flds	-4(%ebp)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	getFPUreturnFPU, .-getFPUreturnFPU
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	# REZERWUJ 20 BAJTÓW PAMIĘCI
	subl	$20, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	flds	.LC0@GOTOFF(%eax)
	# ZMNIEJSZ WARTOŚĆ ESP o -4+ESP (POWIĘKSZ STOS O 32 BITY?)
	leal	-4(%esp), %esp
	# ZDEJMIJ ST(0) Z FPU, ZAPISZ NA STOSIE
	fstps	(%esp)
	# KOPIUJ .LC1@GOTOFF(%eax) ??? DO ST(0)
	flds	.LC1@GOTOFF(%eax)
	# ODEJMIJ 4 OD ESP ???
	leal	-4(%esp), %esp
	# ZDEJMI ST(0) ZE STOSU, ZAPISZ POD ADRESEM ESP
	fstps	(%esp)
	# WYWOŁAJ FUNKCJĘ MNOŻĄCĄ
	# NA STOSIE 2 WARTOŚCI FLOAT 32 BITY
	call	getFPUreturnFPU
	# W ST(0) WYNIK OBLICZEŃ
	# ZMIEJSZENIE STOSU O 8 BAJTÓw
	addl	$8, %esp
	# ZDEJMIJ  ST(0), ZAPISZ W -20+EBP
	fstps	-20(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1077936128
	.align 4
.LC1:
	.long	1073741824
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB2:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE2:
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
