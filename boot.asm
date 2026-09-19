mov ah, 0x0e
mov al, 65
int 0x10

print_alphabet:  

    add al, 33
    int 0x10

    cmp al, 122
    je halt_program

    sub al, 31
    int 0x10

    jmp print_alphabet

halt_program:
    hlt

times 510 - ($ - $$) db 0
db 0x55, 0xaa