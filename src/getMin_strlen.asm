;; Arthur Jourdan
;; Epitech MiniLibC
;; getMin.asm

BITS 64

extern getMin
extern strlen

global getMin_strlen
; int getMin_strlen(const char *s1, const char *s2)

section .text

getMin_strlen:
    call strlen
    mov r10, rax
    mov rdi, rsi
    call strlen
    mov r11, rax
    mov rdi, r10
    mov rsi, r11
    call getMin
    ret