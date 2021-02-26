;; Arthur Jourdan
;; Epitech MiniLibC
;; memmove.asm

BITS 64

extern memcpy

global memmove
; void *memmove(void *dest, const void *src, size_t n)

section .text

; memmove:
;     cmp rdx, 0          ; compare third argument with zero
;     je .RET             ; if nb of bytes to move is zero then return
;     cmp rdi, rsi        ; compare first and second arguments
;     jb .REVERSE         ; copy memory starting from end, if first is lower than second
;     call memcpy         ; else do a memcpy
;     mov rdi, rax        ; put return of memcpy into rdi
;     jmp .RET

; .REVERSE:
;     xor rax, rax
;     jmp .LOOP
; .LOOP:
;     mov r10b, BYTE[rsi + rdx]
;     mov BYTE[rdi + rdx], r10b
;     cmp rdx, 0         ; check if counter == third argument
;     jbe .RET            ; if rdx is equal to rdx, return
;     dec rdx
;     jmp .LOOP           ; go to the begining of the loop
; .RET:
;     mov rax, rdi        ; put ptr on first arg into return value
;     ret                 ; return rax


memmove:
    xor rax, rax        ; counter = 0
.LOOP_PUSH:
    cmp     rax, rdx        ; check if counter >= arg3
    jae     .LOOP_POP       ; jump if rax is above or equal to rdx
    movsx   r10, BYTE[rsi + rax]
    push    r10
    inc     rax
    jmp     .LOOP_PUSH           ; go to the begining of the loop
.LOOP_POP:
    cmp rax, 0          ; check if counter >= arg3
    jbe .RET       ; jump if rax is above or equal to rdx
    dec rax
    pop r10
    mov BYTE[rdi + rax], r10b
    jmp .LOOP_POP           ; go to the begining of the loop

.RET:
    mov rax, rdi        ; put ptr on first arg into return value
    ret ; return rax
