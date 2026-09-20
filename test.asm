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

    jmp input_string

end:

jmp $

buffer: times 32 + 1 db 0

times 510 - ($ - $$) db 0
db 0x55, 0xaa