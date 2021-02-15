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
    jbe end_getMin
    mov rax, rsi
end_getMin:
    ret ; return rax