.bss
    control_word: .short 0

.text
.global round_up, round_down, to_nearest
.type round_up, @function
.type round_down, @function
.type to_nearest, @function

round_up:
    push    %ebp
    mov     %esp, %ebp

    mov     $0, %eax
    fstcw   control_word
    mov     control_word, %ax
    bts $11, %ax
    btr $10, %ax
    mov     %ax, control_word
    fldcw   control_word

    mov     %ebp, %esp
    pop     %ebp
    ret

round_down:
    push    %ebp
    mov     %esp, %ebp

    mov     $0, %eax
    fstcw   control_word
    mov     control_word, %ax
    bts $10, %ax
    btr $11, %ax
    mov     %ax, control_word
    fldcw   control_word

    mov     %ebp, %esp
    pop     %ebp
    ret

to_nearest:
    push    %ebp
    mov     %esp, %ebp

    mov     $0, %eax
    fstcw   control_word
    mov     control_word, %ax
    btr $10, %ax
    btr $11, %ax
    mov     %ax, control_word
    fldcw   control_word

    mov     %ebp, %esp
    pop     %ebp
    ret