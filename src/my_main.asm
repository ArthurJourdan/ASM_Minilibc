

global _start

extern putstr
extern strlen

%macro exit 1
    mov rax, 60         ; syscall id for exit
    mov rdi, %1         ; first arg taken by exit is return value here argument 1
    syscall
%endmacro

section .data
    string: db "test_defined_bytes", 10, 0
    length: equ $-string ;; number of characters in string

section .text

_start:
    mov rdi, string
    call strlen
    test rax, length
    jne end
    call putstr
    call end

end:
    exit 0