SYSCALL32 = 0x80 # wywołanie funkcji standardowej
EXIT = 1 # nr funkcji restartu (=1) – zwrot sterowania do s.o.
EXIT_SUCCESS = 0

.text
.global main

.extern zmiennaX

main:
    call wyswietl

    push $1
    push $2
    push $3

    call sumuj

    pop %eax
    pop %eax
    pop %eax

    mov zmiennaX, %eax
    inc %eax
    mov %eax, zmiennaX

    call wyswietl

# zakończenie wykonywania programu
mov $EXIT, %eax 
mov $EXIT_SUCCESS, %ebx

int $SYSCALL32