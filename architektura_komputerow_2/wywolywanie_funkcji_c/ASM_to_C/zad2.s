.text
.global myTimer, addThreeNumbers
myTimer:

# poczatek funkcji

push %ebp # ebp - stack frame pointer (zachowanie bazowego adresu ramki dla callera)
mov %esp, %ebp # esp - stack pointer (ustalenie adresu ramki bazowej na szczyt stosu callera)
push %ebx # ??
# przygotowanie do wywolania zegara

xor %eax, %eax
xor %edx, %edx
cpuid

# wywolanie zegara i zapisanie go do edx:eax

rdtsc

# zakonczenie funkcji
pop %ebx
mov %ebp, %esp
pop %ebp

ret

addThreeNumbers:
    push %ebp # ebp - stack frame pointer (zachowanie bazowego adresu ramki dla callera)
    mov %esp, %ebp # esp - stack pointer (ustalenie adresu ramki bazowej na szczyt stosu callera)
    push %ebx # ??

    mov $0, %eax
    mov 8(%ebp), %ebx
    add %ebx, %eax
    mov 12(%ebp), %ebx
    add %ebx, %eax
    mov 16(%ebp), %ebx
    add %ebx, %eax

    pop %ebx
    mov %ebp, %esp
    pop %ebp

    ret