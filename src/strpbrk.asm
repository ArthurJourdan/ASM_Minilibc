;; Arthur Jourdan
;; Epitech MiniLibC
;; strpbrk.asm

BITS 64

global strpbrk
; char *strpbrk(const char *s, int c)

section .text

strpbrk:
    xor rax, rax        ; size = 0
.LOOP:
    cmp BYTE[rdi], 0
    je .NOT_FOUND
    jmp .CHECK_ACCEPT

.CHECK_ACCEPT:
    xor rcx, rcx        ; counter for ACCEPT loop = 0
.LOOP_ACCEPT:
    mov r10b, BYTE[rdi]
    cmp r10b, BYTE[rsi + rcx]    ; compare characters
    je .RET        ; if characters are the same, do not increase size, continue main loop
    cmp BYTE[rsi + rcx], 0
    je .CONTINUE
    inc rcx
    jmp .LOOP_ACCEPT

.CONTINUE:
    inc rdi
    jmp .LOOP

.NOT_FOUND:
    mov rdi, 0
    jmp .RET

.RET:
    mov rax, rdi
    ret