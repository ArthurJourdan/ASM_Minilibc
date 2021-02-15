;; Arthur Jourdan
;; Epitech MiniLibC
;; strchr.asm

BITS 64

global my_strchr
; char *strchr(const char *s, int c)

section .text

my_strchr:
    cmp BYTE[rdi], 0 ; if end of the string
    je end_not_found ; if check is true, return NULL
    cmp BYTE[rdi], sil ; check if this char == char in arg2
    je end_strchr ; if check is true, go to function end
    inc rdi
    jmp my_strchr ; go to the begining of the loop
end_not_found:
    xor rdi, rdi ; set rdi to NULL
end_strchr:
    mov rax, rdi
    ret ; return rax