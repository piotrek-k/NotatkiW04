.text
.global myTimer, addThreeNumbers

# .type myTimer,@function (informacja dla komilatora, że to funkcja)
myTimer:
    # poczatek funkcji

    push %ebp # ebp - stack frame pointer (zapisz bazową pozycję stosu funkcji wywołującej)
    mov %esp, %ebp # esp - stack pointer (szczyt stosu funkcji wywołującej będzie pozycją bazową dla naszego stosu)
    push %ebx # ?? w ProgrammingFromGroundUp: subl $4, %esp. Daje chyba ten sam efekt, coś z przeniesieniem pozycji wskaźnika stosu.
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