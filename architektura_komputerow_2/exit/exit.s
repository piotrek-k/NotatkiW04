# assembler directive
# this is where you list any memory storage you will need for data
.section .data

# this section is where program instructions live
.section .text

# instructs assembler that _start is important to remember
# .globl means that the assembler shouldn't discard symbol after assembly
# _start is a special symbol that always needs to be marked with .globl because it marks the location of the start of the program
.globl _start

# _start is a symbol. it's used to locate programs or data
_start:
# transfers literal number 1 into %eax register
# ommitting "$" would load data from adress 1
movl $1, %eax
# we moved 1 to eax since we are preparing to call Linux kernel
# 1 is "exit" system call
movl $2, %ebx
# we moved 0 to ebx since it's where linux "exit" takes parameter from

# "int" stands for "interrupt". Transfers control from our program to Linux. Perform system call
int $0x80
# Linux knows which system call we want to access by what we stored in the %eax register
