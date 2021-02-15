;; Arthur Jourdan
;; Epitech MiniLibC
;; memcpy.asm

BITS 64

global my_memcpy
; void *memcpy(void *dest, const void *src, size_t n)

section .text

my_memcpy:
    xor rax, rax ; counter = 0
loop_memcpy:
    cmp rax, rdx ; check if counter >= arg3
    jae end_memcpy ; jump if rax is above or equal to rdx
    mov r10, [rsi + rax]
    mov [rdi + rax], r10
    inc rax
    jmp loop_memcpy ; go to the begining of the loop
end_memcpy:
    mov rax, rdi
    ret ; return rax