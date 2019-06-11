.data
    formatchar: .ascii "\0"      # do pomiaru scanf

.bss
    .comm measured_time, 4
    .comm char, 1               # do pomiaru scanf

.text
.global measure_register_op, measure_memory_read, measure_read_os_function, measure_scanf_os_function
.type measure_register_op, @function
.type measure_memory_read, @function
.type measure_read_os_function, @function


# Funkcja odczytujaca ilość taktowań procesora od czasu uruchomienia
getCurrentTime:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx          # zachować EBX dla funkcji wywołującej (caller)

    xorl %eax, %eax
    cpuid               # serialize instruction execution
    rdtsc               # wynik do edx:eax

    popl %ebx

    mov %ebp, %esp
    popl %ebp

    ret

measure_register_op:
    # Zmierz czas wykonania operacji movl

    # inicjalizacja funckji
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    pushl %edi

    xor %edi, %edi

    # pierwszy pomiar
    xorl %eax, %eax
    cpuid               # synchornizacja wątków
    rdtsc               # wynik w edx:eax

    # operacja na której dokonujemy pomiaru
    movl %eax, %edi     

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

measure_memory_read:
    # Zmierz czas operacji na pamięci

    pushl %ebp
    movl %esp, %ebp
    pushl %ebx

    xorl %eax, %eax
    cpuid                       # serialize instruction execution
    rdtsc                       # wynik do edx:eax

    movl %eax, measured_time    # zakładam, że dane z EDX nie zmienią się
                                # w tak krótkim czasie

    cpuid                       # serialize instruction execution
    rdtsc                       # wynik do edx:eax

    movl measured_time, %ebx    # odczytanie pierwszego czasu do EBX
    sub %ebx, %eax              # roznica czasow

    # movl %ebx, %eax

    popl %ebx
    mov %ebp, %esp
    popl %ebp

    ret

measure_read_os_function:
    # Zmierz czas trwania funkcji systemowej read()

    pushl %ebp
    movl %esp, %ebp
    pushl %ebx

    xorl %eax, %eax
    cpuid                       # serialize instruction execution
    rdtsc                       # wynik do edx:eax

    movl %eax, %edi             # Czas startowy

    call read

    cpuid                       # serialize instruction execution
    rdtsc                       # wynik do edx:eax

    movl %edi, %ebx             # odczytanie pierwszego czasu do EBX
    sub %ebx, %eax              # roznica czasow

    # movl %ebx, %eax

    popl %ebx
    mov %ebp, %esp
    popl %ebp

    ret

measure_scanf_os_function:
    # Zmierz czas trwania funkcji systemowej scanf()

    pushl %ebp
    movl %esp, %ebp
    pushl %ebx

    xorl %eax, %eax
    cpuid                       # serialize instruction execution
    rdtsc                       # wynik do edx:eax

    movl %eax, %edi             # Czas startowy

    # pobranie char ze scanf
	mov $0, %eax
	push $char					# parametr: adres do `char`
	push $formatchar
	call scanf
	pop %eax
	pop %eax

    cpuid                       # serialize instruction execution
    rdtsc                       # wynik do edx:eax

    movl %edi, %ebx             # odczytanie pierwszego czasu do EBX
    sub %ebx, %eax              # roznica czasow

    # movl %ebx, %eax

    popl %ebx
    mov %ebp, %esp
    popl %ebp

    ret
