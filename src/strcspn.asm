;; Arthur Jourdan
;; Epitech MiniLibC
;; strcspn.asm

BITS 64

global strcspn
; size_t strcspn(const char *s, const char *reject)

section .text

strcspn:
    xor rax, rax        ; size = 0
    xor rbx, rbx        ; counter for main loop = 0
.LOOP:
    cmp BYTE[rdi + rbx], 0
    je .RET
    jmp .CHECK_REJECT

.CHECK_REJECT:
    xor rcx, rcx        ; counter for reject loop = 0
.LOOP_REJECT:
    mov r10b, BYTE[rdi + rax]
    cmp r10b, BYTE[rsi + rcx]    ; compare characters
    je .CONTINUE        ; if characters are the same, do not increase size, continue main loop
    cmp BYTE[rsi + rcx], 0
    je .ACCEPT
    inc rcx
    jmp .LOOP_REJECT
.ACCEPT:
    inc rax
    jmp .CONTINUE


.CONTINUE:
    inc rbx
    jmp .LOOP

.RET:
    ret