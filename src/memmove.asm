;; Arthur Jourdan
;; Epitech MiniLibC
;; memmove.asm

BITS 64

extern memcpy

global memmove
; void *memmove(void *dest, const void *src, size_t n)

section .text

memmove:
    cmp rdx, 0          ; compare third argument with zero
    je .RET             ; if nb of bytes to move is zero then return
    cmp rdi, rsi        ; compare first and second arguments
    jb .REVERSE         ; copy memory starting from end, if first is lower than second
    call memcpy         ; else do a memcpy
    mov rdi, rax        ; put return of memcpy into rdi
    jmp .RET

.REVERSE:
    xor rax, rax
    jmp .LOOP
.LOOP:
    mov r10b, BYTE[rsi + rdx]
    mov BYTE[rdi + rdx], r10b
    cmp rdx, 0         ; check if counter == third argument
    jbe .RET            ; if rdx is equal to rdx, return
    dec rdx
    jmp .LOOP           ; go to the begining of the loop
.RET:
    mov rax, rdi        ; put ptr on first arg into return value
    ret                 ; return rax
