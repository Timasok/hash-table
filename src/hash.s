section .text

global _start

_start:     
        jmp GNU_hash_asm                ; хэш-функция, по максимуму использующая регистры

section .data
Msg:    dq "Bitch", 0x0a
section .text

GNU_hash_asm:
        mov rdi, Msg                    ; test shit

        ; push    rbp
        ; mov     rbp, rsp              ; Заголовок функции

        push rbx
        xor rbx, rbx                    ; rbx = 0
        
        mov rdx, [rdi]                  ; rdx = string
        mov rax, 6287                   ; r9 = hash
        
        jmp .first_check

.make_step:
        mov ebx, eax                    ; ebx = eax(hash)
        sal ebx, 5                      ; ebx = hash << 5
        movsx rbx, ebx
        add rax, rbx                    ; rax = (hash << 5 + hash)
        
        xor rbx, rbx
        mov bl, dl                      ; rbx = string[idx]
        add rax, rbx

        jmp .check_loop

.first_check:
        cmp dl, 0                       ; if(string[idx] == '\0')
        je .end                         ;   break;        
        
        mov rcx, 7                      ; rcx = set counter
        jmp .make_step

.check_loop:
        sar rdx, 8                      ; get next letter in
        cmp dl, 0                       ; if(string[idx] == '\0')
        je .end                         ;   break;

        loop .make_step
.end:
        and rax, 0xffffffff
        pop rbx
        ; pop rbp
        ret

