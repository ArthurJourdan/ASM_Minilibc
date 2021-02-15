;; Arthur Jourdan
;; Epitech MiniLibC
;; getMax.asm

BITS 64

global getMax
; int getMax(int x, int y)

section .text

getMax:
    ; mov rax, 0
    mov rax, rdi
    cmp rax, rsi
    jae end_getMax
    mov rax, rsi
end_getMax:
    ret ; return rax