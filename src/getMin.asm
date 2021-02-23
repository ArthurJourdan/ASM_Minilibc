;; Arthur Jourdan
;; Epitech MiniLibC
;; getMin.asm

BITS 64

global getMin
; int getMin(int x, int y)

section .text

getMin:
    ; mov rax, 0
    mov rax, rdi
    cmp rax, rsi
    jbe .RET
    mov rax, rsi
.RET:
    ret ; return rax