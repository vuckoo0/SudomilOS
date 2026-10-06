global _start
extern main

section .text
    bits 32
    _start:
        call main
        jmp $