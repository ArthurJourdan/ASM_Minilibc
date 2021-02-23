;; Arthur Jourdan
;; Epitech MiniLibC
;; rindex.asm

BITS 64

global rindex
; char *rindex(const char *s, int c)

section .text

rindex:
    xor r10, r10
.LOOP:
    cmp BYTE[rdi], sil
    jne .NOT_FOUND
    mov r10, rdi
.NOT_FOUND:
    cmp BYTE[rdi], 0
    je  .RET
    inc rdi
    jmp .LOOP

.RET:
    mov rax, r10
    ret
