mov ah, 0x0e
mov al, 65
int 0x10

print_alphabet:

    inc al
    int 0x10

    cmp al, 90
    je loop_forever

    jmp print_alphabet

loop_forever:
    jmp $

times 510 - ($ - $$) db 0
db 0x55, 0xaa