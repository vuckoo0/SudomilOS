[org 0x7c00]

mov bx, buffer

input_string:

    mov ah, 0
    int 0x16

    cmp al, 0x0d
    je end
    
    cmp bx, buffer + 32
    je input_string

    mov [bx], al
    inc bx

    mov ah, 0x0e
    int 0x10
    jmp input_string

end:

    mov ah, 0x0e

    mov bx, newline
    call print_string

    mov bx, exit_statement
    call print_string

    mov bx, buffer
    call print_string

    mov bx, newline
    call print_string

    jmp loop_forever

print_string:

    mov al, [bx]

    cmp al, 0
    jne skip
    ret
    skip:

    int 0x10
    inc bx
    jmp print_string

loop_forever:
    jmp $

buffer: times 32 + 1 db 0
exit_statement: db "Bye ", 0
newline: db 0x0d, 0x0a, 0

times 510 - ($ - $$) db 0
db 0x55, 0xaa