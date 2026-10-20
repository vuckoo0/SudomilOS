global _start
extern main

section .text
    bits 32
    _start:
        mov esp, 0x90000
        call main
        jmp $