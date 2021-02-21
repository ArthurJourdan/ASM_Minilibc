;; Arthur Jourdan
;; Epitech MiniLibC
;; strcmp.asm

BITS 64

extern strlen
extern getMax

global strcmp
global strncmp
; int strcmp(const char *s1, const char *s2)
; int strncmp(const char *s1, const char *s2, size_t n)

section .text

strcmp:
    call strlen
    mov r12, rax ; put length of string in r12
    xor al, al
    jmp loop_strcmp

strncmp:
    mov r10, rdi
    mov r11, rsi
    mov rdi, rdx
    call strlen ; get length of string so that if the 3rd argument is a number bigger than the length, can still stop the program
    mov rsi, rax ; put result of strlen into rsi
    call getMax ; get max between third argument and length of string
    mov r12, rax ; put result of getMax into r12 which is a stopper value to stop comparison if lboth strings have the same values
    mov rdi, r10
    mov rsi, r11
    xor al, al
    jmp loop_strcmp

loop_strcmp:
    mov al, BYTE[rdi]
    sub al, BYTE[rsi]
    cmp al, 0 ; check if difference between char of s1 and char of s2 == 0
    jne end_strcmp ; jump if al (aka difference) is not rqueax to 0
    inc rdi
    inc rsi
    dec r12
    cmp r12, 0
    jb end_strcmp ; if length of s1 has been traveled, end program
    jmp loop_strcmp ; go to the begining of the loop
end_strcmp:
    ret ; return al