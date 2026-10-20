// Kernel/cpu/pic.c
#include "ports.h"

#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

void pic_remap() {
    // save masks
    uint8_t mask1 = port_read(PIC1_DATA);
    uint8_t mask2 = port_read(PIC2_DATA);

    // start init sequence (cascade mode)
    port_write(PIC1_CMD,  0x11);
    port_write(PIC2_CMD,  0x11);

    // set vector offsets: IRQ0-7 → 32-39, IRQ8-15 → 40-47
    port_write(PIC1_DATA, 0x20);   // master offset = 32
    port_write(PIC2_DATA, 0x28);   // slave offset  = 40

    // tell master it has a slave at IRQ2, tell slave its cascade identity
    port_write(PIC1_DATA, 0x04);
    port_write(PIC2_DATA, 0x02);

    // 8086 mode
    port_write(PIC1_DATA, 0x01);
    port_write(PIC2_DATA, 0x01);

    // restore masks
    port_write(PIC1_DATA, mask1);
    port_write(PIC2_DATA, mask2);
}

void pic_unmask(uint8_t irq) {
    uint16_t port = (irq < 8) ? PIC1_DATA : PIC2_DATA;
    if (irq >= 8) irq -= 8;
    uint8_t mask = port_read(port);
    port_write(port, mask & ~(1 << irq));
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8)
        port_write(PIC2_CMD, 0x20);   // tell slave
    port_write(PIC1_CMD, 0x20);       // always tell master
}