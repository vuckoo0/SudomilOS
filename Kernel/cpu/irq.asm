; Kernel/cpu/irq.asm
global irq1     ; keyboard

extern irq1_handler

irq1:
    cli
    pusha
    call irq1_handler
    popa
    sti
    iret