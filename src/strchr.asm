;; Arthur Jourdan
;; Epitech MiniLibC
;; strchr.asm

BITS 64

global strchr
; char *strchr(const char *s, int c)

section .text

strchr:
    cmp BYTE[rdi], sil  ; check if this char == char in arg2
    je  .RET            ; if check is true, go to function end
    cmp BYTE[rdi], 0    ; if end of the string
    je  .NOT_FOUND      ; if check is true, return NULL
    inc rdi
    jmp strchr          ; go to the begining of the loop
.NOT_FOUND:
    xor rdi, rdi        ; set rdi to NULL, then return
.RET:
    mov rax, rdi        ; set return value to actual char in the string
    ret                 ; return rax