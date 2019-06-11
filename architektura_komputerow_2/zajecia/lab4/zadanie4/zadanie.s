.data
    formatchar: .ascii "\0"      # do pomiaru scanf

.bss
    .comm measured_time, 4
    .comm char, 1               # do pomiaru scanf

.text
.global measure_independent_op, measure_dependent_op
.type measure_independent_op, @function
.type measure_dependent_op, @function


measure_independent_op:
    # Zmierz czas wykonania sekwencji niezaleznych operacji

    # inicjalizacja funkcji
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    pushl %edi

    xor %edi, %edi

    # pierwszy pomiar
    xorl %eax, %eax
    cpuid               # synchornizacja wątków
    rdtsc               # wynik w edx:eax

    movl %eax, %edi

    xor %eax, %eax
    xor %ebx, %ebx
    xor %ecx, %ecx
    xor %edx, %edx

    # ###############
    # operacje na których dokonujemy pomiaru
    # nie uzywac %edi
    
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx
    addl %eax, %ebx
    addl %ecx, %edx

    # ###############

    # drugi pomiar
    cpuid               # synchornizacja wątków
    rdtsc               # wynik w edx:eax

    # różnica czasów
    sub %edi, %eax

    # Wynik w EAX. EAX będzie zwrócone przez funkcję

    # End of function
    popl %edi
    popl %ebx
    mov %ebp, %esp
    popl %ebp

    ret

measure_dependent_op:
    # Zmierz czas wykonania sekwencji zaleznych operacji

    # inicjalizacja funkcji
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    pushl %edi

    xor %edi, %edi

    # pierwszy pomiar
    xorl %eax, %eax
    cpuid               # synchornizacja wątków
    rdtsc               # wynik w edx:eax

    movl %eax, %edi

    xor %eax, %eax
    xor %ebx, %ebx
    xor %ecx, %ecx
    xor %edx, %edx

    # ###############
    # operacje na których dokonujemy pomiaru
    # nie uzywac %edi
    
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax
    addl %eax, %ebx
    addl %ebx, %ecx
    addl %ecx, %edx
    addl %edx, %eax

    # ###############

    # drugi pomiar
    cpuid               # synchornizacja wątków
    rdtsc               # wynik w edx:eax

    # różnica czasów
    sub %edi, %eax

    # Wynik w EAX. EAX będzie zwrócone przez funkcję

    # End of function
    popl %edi
    popl %ebx
    mov %ebp, %esp
    popl %ebp

    ret