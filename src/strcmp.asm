;; Arthur Jourdan
;; Epitech MiniLibC
;; strcmp.asm

BITS 64

extern strlen
extern getMax

global strcmp:function
; int strcmp(const char *s1, const char *s2)

section .text

strcmp:
    call strlen
    mov r12, rax ; put length of string in r12
    xor al, al
    jmp .LOOP

.LOOP:
    mov al, BYTE[rdi]
    sub al, BYTE[rsi]
    cmp al, 0 ; check if difference between char of s1 and char of s2 == 0
    jne .RET ; jump if al (aka difference) is not equal to 0
    inc rdi
    inc rsi
    dec r12
    cmp r12, 0
    jb .RET ; if length of s1 has been traveled, end program
    jmp .LOOP ; go to the begining of the lOOP

.RET:
    ret ; return al