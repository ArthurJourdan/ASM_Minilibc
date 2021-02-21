;; Arthur Jourdan
;; Epitech MiniLibC
;; memmove.asm

BITS 64

global memmove
; void *memmove(void *dest, const void *src, size_t n)

section .text

memmove:
    mov rax, 0 ; counter = 0
loop_memmove:
    cmp rax, rdx ; check if counter < arg3
    jae end_memmove ; jump if rax is above or equal to rdx
    mov rcx, [rsi + rax]
    mov [rdi + rax], rcx
    inc rax
    jmp loop_memmove ; go to the begining of the loop
end_memmove:
    mov rax, rdi
    ret ; return rax