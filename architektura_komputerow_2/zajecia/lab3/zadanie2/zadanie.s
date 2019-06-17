.text
.global count           # .global makes the symbol visible to ld
.type count, @function  # Mark the symbol as being a function name. 

count:
    pushl %ebp
    movl %esp, %ebp

    pushl %ebx          # zachować EBX dla funkcji wywołującej (caller)

    movl $0, %eax
    movl $0, %edx
    cpuid               # serialize instruction execution
    rdtsc               # wynik do edx:eax

    popl %ebx

    mov %ebp, %esp
    popl %ebp

ret
