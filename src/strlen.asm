;; Arthur Jourdan
;; Epitech MiniLibC
;; strlen.asm

BITS 64

global strlen:function ; ask kyllian if optimization
; size_t strlen(const char *s)

section .text

strlen:
    push rbp
    mov rbp, rsp
    xor rax, rax ; counter = 0
loop_strlen:
    cmp BYTE[rdi + rax], 0 ; check if this char == '\0'
    je end_strlen ; if check is true, go to function end
    inc rax
    ; inc rdi
    jmp loop_strlen ; go to the begining of the loop
end_strlen:
    leave
    ret ; return rax aka the length of the string passed as parameter