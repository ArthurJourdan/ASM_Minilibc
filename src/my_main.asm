

global _start

extern my_putstr
extern my_strlen

%macro my_exit 1
    mov rax, 60         ; syscall id for exit
    mov rdi, %1         ; first arg taken by exit is return value here argument 1
    syscall
%endmacro

section .data
    my_string: db "test_defined_bytes", 10, 0
    my_length: equ $-my_string ;; number of characters in my_string

section .text

_start:
    mov rdi, my_string
    call my_strlen
    test rax, my_length
    jne end
    call my_putstr
    call end

end:
    my_exit 0