.bss
    control_word: .short 0

.data
    first_num: .double 1.0
    second_num: .double 3.0

.text
.global enable_32bit_precision, put_result_on_stack, enable_64bit_precision, enable_80bit_precision
.type enable_32bit_precision, @function
.type enable_64bit_precision, @function
.type enable_80bit_precision, @function
.type put_result_on_stack, @function

put_result_on_stack:
    push    %ebp
    mov     %esp, %ebp

    
    fldl second_num
    fldl first_num
    # secondnum - st(1)
    # firstsum - st(0)
    fdiv %st, %st(1)
    # fxch %st(1)
    fstp %st                    # w pamięci zostaje tylko wynik dzielenia

    STOP_HERE:

    mov     %ebp, %esp
    pop     %ebp
    ret

enable_32bit_precision:
    push    %ebp
    mov     %esp, %ebp

    mov     $0, %eax
    fstcw   control_word
    mov     control_word, %ax
    btr $8, %ax
    btr $9, %ax
    mov     %ax, control_word
    fldcw   control_word

    mov     %ebp, %esp
    pop     %ebp
    ret

enable_64bit_precision:
    push    %ebp
    mov     %esp, %ebp

    mov     $0, %eax
    fstcw   control_word
    mov     control_word, %ax
    bts $9, %ax
    btr $8, %ax
    mov     %ax, control_word
    fldcw   control_word

    mov     %ebp, %esp
    pop     %ebp
    ret

enable_80bit_precision:
    push    %ebp
    mov     %esp, %ebp

    mov     $0, %eax
    fstcw   control_word
    mov     control_word, %ax
    bts $8, %ax
    bts $9, %ax
    mov     %ax, control_word
    fldcw   control_word

    mov     %ebp, %esp
    pop     %ebp
    ret