;; Arthur Jourdan
;; Epitech MiniLibC
;; memset.asm

BITS 64

extern my_putstr

global my_memset
; void *memset(void *s, int c, size_t n)

section .text

my_memset:
    xor rax, rax ; counter = 0
loop_memset:
    cmp rax, rdx ; check if counter >= arg3
    jae end_memset ; jump if rax is above or equal to rdx
    mov BYTE[rdi + rax], sil ; put int c into the void *s, at index rax
    inc rax
    jmp loop_memset ; go to the begining of the loop
end_memset:
    mov rax, rdi
    ret ; return rax