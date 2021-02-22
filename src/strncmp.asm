;; Arthur Jourdan
;; Epitech MiniLibC
;; strncmp.asm

extern strlen
extern getMax

global strncmp:function
; int strncmp(const char *s1, const char *s2, size_t n)

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
    jmp .LOOP

.LOOP:
    mov al, BYTE[rdi]
    sub al, BYTE[rsi]
    cmp al, 0 ; check if difference between char of s1 and char of s2 == 0
    jne .RET ; jump if al (aka difference) is not equal to 0
    inc rdi
    inc rsi
    dec r12
    cmp r12, 0
    jb .RET ; if length of s1 has been traveled, end program
    jmp .LOOP ; go to the begining of the lOOP

.RET:
    ret ; return al