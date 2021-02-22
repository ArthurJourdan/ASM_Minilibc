;; Arthur Jourdan
;; Epitech MiniLibC
;; memcpy.asm

BITS 64

global memcpy
; void *memcpy(void *dest, const void *src, size_t n)

section .text

memcpy:
    xor rax, rax        ; counter = 0
    jmp .LOOP
.LOOP:
    cmp rax, rdx        ; check if counter >= arg3
    jae .RET            ; jump if rax is above or equal to rdx
    mov r10b, BYTE[rsi + rax]
    mov BYTE[rdi + rax], r10b
    inc rax
    jmp .LOOP           ; go to the begining of the loop
.RET:
    mov rax, rdi        ; put ptr on first arg into return value
    ret ; return rax

;   here is an other version,
;   incrementing pointer instead of using index
; .LOOP:
    ; cmp rax, rdx    ; check if counter >= arg3
    ; jae .RET        ; jump if rax is above or equal to rdx
    ; mov r10, [rsi]
    ; mov [rdi], r10
    ; inc rax
    ; inc rdi
    ; inc rsi         ; put ptr on first arg into return value
    ; jmp .LOOP       ; go to the begining of the loop