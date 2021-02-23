;; Arthur Jourdan
;; Epitech MiniLibC
;; strncmp.asm

extern strlen
extern getMax

global strncmp:function
; int strncmp(const char *s1, const char *s2, size_t n)

strncmp:
    xor rcx, rcx
    jmp .LOOP

.LOOP:
    xor al, al
    cmp rcx, rdx            ; if counter is above or equal to third argument
    jae .RET                ; then return
    mov al, BYTE[rdi + rcx] ; put char of rdi at index rcx in al
    sub al, BYTE[rsi + rcx] ; substract char of rsi at index rcx to al --> make difference
    cmp al, 0               ; check if difference between char of s1 and char of s2 == 0
    jne .RET                ; jump if al (aka difference) is not equal to 0
    inc rcx                 ; counter++
    jmp .LOOP               ; go to the begining of the lOOP

.RET:
    movsx   rax, al         ; return value compatible to int, keeping the sign
    ret                     ; return al