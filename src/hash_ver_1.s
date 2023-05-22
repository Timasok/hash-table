section .text
global hash_gnu_asm
hash_gnu_asm:
        push rbx
        xor rbx, rbx                    ; rbx = 0       
        mov rdx, [rdi]                  ; rdx = string
        mov eax, 6287d                   ; r9 = hash
        jmp .first_check
.make_step:
        mov ebx, eax                    ; ebx = eax(hash)
        shl ebx, 5                      ; ebx = hash << 5
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
        dec rcx
        jnz .make_step
.end:
        pop rbx
        ret