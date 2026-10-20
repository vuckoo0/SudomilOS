// Kernel/cpu/pic.h
#ifndef PIC_H
#define PIC_H

#include <stdint.h>

extern void irq1(void);

void pic_remap();
void pic_unmask(uint8_t irq);
void pic_send_eoi(uint8_t irq);

#endif