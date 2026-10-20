global isr0
extern isr0_handler

isr0:
    cli
    pusha
    call isr0_handler
    popa
    sti
    iret