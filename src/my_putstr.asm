
BITS 64

extern my_strlen

global my_putstr
; int puts(const char *s)

section .text

my_putstr:
    push rbp
    mov rbp, rsp
    mov rsi, rdi ; put arg1 which is the string to print into second argument of write
    call my_strlen ; rax set to strlen of rdi
    mov rdx, rax ; put length of string into syscall write's third argument, rax being the return value of my_strlen
    mov rax, 1 ; write syscall
    mov rdi, 1 ; filedescriptor of stdout in rdi register
    syscall
    mov rax, rdx ; put nb of characters printed into return value
    leave
    ret ; return nb of chars printed