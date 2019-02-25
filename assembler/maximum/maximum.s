# BUILDING
# as maximum.s -o ./build/maximum.o
# ld ./build/maximum.o -o ./build/maximum

# VARIABLES: The registers have the following uses:
#
# %edi - Holds the index of the data item being examined
# %ebx - Largest data item found
# %eax - Current data item
#
# The following memory locations are used:
#
# data_items - contains the item data.  A 0 is used
#              to terminate the data
#

.section .data

data_items:
# .long reserves memory for list of numbers that follows it
# data_items refers to the location of first item
# .long means each number takes four storage location (bytes?)
.long 3,67,34,222,45,75,54,34,44,33,22,11,66,0 # total size: 14x4=56 bytes
# no .globl in data_items. no other program needs to know where list of items is located
# strange results will appear if we add number larger than 255. It exceeds largest allowed exit status

.section .text

.globl _start

_start:
movl $0, %edi # move 0 into index register
movl data_items(,%edi,4), %eax
movl %eax, %ebx # since it's first item, %eax is the biggest

start_loop:
    cmpl $0, %eax # check if current number is 0 (if it is, exit)
    je loop_exit
    incl %edi # load next value
    movl data_items(,%edi,4), %eax # start at data_items, take data number %edi that is taking 4 bytes. move it to %eax
    # ADDRESS_OR_OFFSET(%BASE_OR_OFFSET,%INDEX,MULTIPLIER)
    # which means FINAL ADDRESS = ADDRESS_OR_OFFSET + %BASE_OR_OFFSET + MULTIPLIER * %INDEX
    cmpl %ebx, %eax # compare values. result stored in %eflags register
    jle start_loop # jump to loop beginning if the new one isn't bigger
    movl %eax, %ebx # it's bigger. %eax is largest
    jmp start_loop # jump to loop beginning

loop_exit:
    # %ebx is the status code for the exit system call
    # and it already has the maximum number
    movl $1, %eax # 1 is the exit() syscall
    int $0x80
