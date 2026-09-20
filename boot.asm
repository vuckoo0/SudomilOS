[org 0x7c00]

mov ah, 0x0e
mov bx, wecome_statement

print_string:

    mov al, [bx]

    cmp al, 0
    je halt_program

    int 0x10
    inc bx

    jmp print_string

wecome_statement:
    db "Welcome to SudomilOS", 0

halt_program:
    hlt

times 510 - ($ - $$) db 0
db 0x55, 0xaa