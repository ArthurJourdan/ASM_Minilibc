;; Arthur Jourdan
;; Epitech MiniLibC
;; strstr.asm

BITS 64

extern strlen
extern strncmp

global strstr
; char *strstr(const char *haystack, const char *needle)

section .text

strstr:
    mov r10, rdi    ; reverse two args
    mov rdi, rsi    ; to be able to use strlen on second
    mov rsi, r10    ; easily
.LOOP:
    cmp BYTE[rsi], 0
    je .NOT_FOUND
    call strlen
    mov rdx, rax
    call strncmp
    cmp rax, 0
    je .RET
    inc rsi
    jmp .LOOP

.NOT_FOUND:
    mov rsi, 0
    jmp .RET

.RET:
    mov rax, rsi
    ret