	.file	"double.c"
	.text
	.globl	getDoubleReturnDouble
	.type	getDoubleReturnDouble, @function
getDoubleReturnDouble:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	# WYGLĄDA JAK KOPIOWANIE PARTIAMI
	# PARAMETRÓW DO ZMIENNYCH LOKALNYCH
	# WSZYSTKICH 24 BAJTÓW (3 double każdy po 8 bajtów)
	# REJESTR MA POŁOWĘ WIELKOŚCI DOUBLE
	movl	8(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	20(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	24(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	28(%ebp), %eax
	movl	%eax, -36(%ebp)
	# ŁADOWANIE Z PAMIĘCI DO ST
	fldl	-24(%ebp)
	# DZIELI ST(0) PRZEZ LICZBĘ POD WSKAZANYM ADRESEM
	fdivl	-32(%ebp)
	# ZDJĘCIE Z ST(0) NA WSKAZANY ADRES
	# ST(1) -> ST(0)
	fstpl	-8(%ebp)
	# ŁADOWANIE Z PAMIĘCI DO ST(0)
	fldl	-40(%ebp)
	# DODANIE ST(0) DO ST(0)? CZYLI MNOŻENIE RAZY 2
	fadd	%st(0), %st
	# ŁADOWANIE PARAMETRU c DO ST(0)
	fldl	-8(%ebp)
	# MNOŻENIE ST(0) * ST(1)
	fmulp	%st, %st(1)
	# ZDJĘCIE ZE STOSU, ZAPIS NA PODANY ADRES
	# ZAPIS NA STOS (ZMIENNA LOKALNA)
	fstpl	-8(%ebp)
	# ŁADOWANIE WYNIKU DO ST(0)
	fldl	-8(%ebp)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	getDoubleReturnDouble, .-getDoubleReturnDouble
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-8, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	fldl	.LC0@GOTOFF(%eax)
	leal	-8(%esp), %esp
	fstpl	(%esp)
	fldl	.LC1@GOTOFF(%eax)
	leal	-8(%esp), %esp
	fstpl	(%esp)
	fldl	.LC2@GOTOFF(%eax)
	leal	-8(%esp), %esp
	fstpl	(%esp)
	call	getDoubleReturnDouble
	addl	$24, %esp
	fstpl	-16(%ebp)
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1075052544
	.align 8
.LC1:
	.long	0
	.long	1074266112
	.align 8
.LC2:
	.long	0
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
