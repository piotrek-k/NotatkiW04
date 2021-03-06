.data
    printf_format: .asciz "%hd \n"
    value1: .float 1.0
    value2: .float 3.0

.bss
    control_word: .short 0


.text
.global main, print_control_word_state
.global change_control_word_at_positon, print_state_of_bit_of_control_word
.global run_fpu_calculations
.type change_control_word_at_positon, @function
.type print_control_word_state, @function
.type print_state_of_bit_of_control_word, @function
.type run_fpu_calculations, @function
 
print_control_word_state:
    push    %ebp
    mov     %esp, %ebp

    # pobranie control_word
    mov     $0, %eax
    fstcw   control_word
    # fwait
    mov     control_word, %ax

    push %eax
    push $printf_format
    call printf
    addl $8, %esp

    mov     %ebp, %esp
    pop     %ebp
    ret

print_state_of_bit_of_control_word:
    push %ebp
    mov %esp, %ebp
    push %ecx
    push %ebx

    movl 8(%ebp), %ebx # pozycja
    fstcw   control_word
    mov     control_word, %cx

    movl $0, %eax
    bt %ebx, %ecx # rezultat we fladze CF
    jc carry_is_set # skocz jeżeli CF=1

    # CF=0:
    movl $0, %eax
    jmp exit_function

    carry_is_set:
    movl $1, %eax
    jmp exit_function

    exit_function:
    pop %ebx
    pop %ecx
    mov     %ebp, %esp
    pop     %ebp
    ret

change_control_word_at_positon:
    # pozycja zaczyna się od 0
    # state = 0 ustawia na 0, state > 0 ustawia na 1

    push %ebp
    mov %esp, %ebp
    push %ebx
    push %ecx

    movl 12(%ebp), %eax # stan
    movl 8(%ebp), %ebx # pozycja
    fstcw   control_word
    mov     control_word, %cx

    cmp $0, %eax
    je bit_to_zero
    # bit_to_one:
    bts %ebx, %ecx
    jmp save_register
    
    bit_to_zero:
    btr %ebx, %ecx
    jmp save_register

    save_register: 
    mov     %cx, control_word
    fldcw   control_word

    pop %ecx
    pop %ebx
    mov     %ebp, %esp
    pop     %ebp
    ret

run_fpu_calculations:
    push %ebp
    mov %esp, %ebp

    flds (value1) 
    flds (value2)
    # value1 w st(1)
    # value2 w st(0)

    fdivrp %st, %st(1)  # dzieli st(1) przez st(0) (czyli value1/value2?), zapisuje wynik
                        # w st(1), zrzuca st(0) ze stosu

    mov     %ebp, %esp
    pop     %ebp

    ret
