;; Arthur Jourdan
;; Epitech MiniLibC
;; strncmp.asm

extern strlen

global strcasecmp:function
; int strncmp(const char *s1, const char *s2, size_t n)

section .text

strcasecmp:
    xor rcx, rcx
    jmp .LOOP

.LOOP:
    mov al, BYTE[rdi + rcx]
    sub al, BYTE[rsi + rcx]
    cmp al, 32
    je .LOOP_TAIL
    cmp al, -32
    je .LOOP_TAIL
    cmp al, 0 ; check if difference between char of s1 and char of s2 == 0
    jne .RET ; jump if al (aka difference) is not equal to 0
.LOOP_TAIL:
    cmp BYTE[rdi + rcx], 0
    je .RET
    cmp BYTE[rsi + rcx], 0
    je .RET
    inc rcx
    jmp .LOOP ; go to the begining of the lOOP

.RET:
    movsx rax, al
    ret ; return al