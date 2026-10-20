#include "idt.h"
#include "isr.h"
#include "pic.h"
#include "../drivers/keyboard/keyboard.h"

struct idt_entry idt[265];
struct idt_ptr idtp;

void idt_set_gate(int num, uint32_t handler, uint16_t selector, uint8_t flags) {
    idt[num].offset_low  = handler & 0xFFFF;
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
    idt[num].selector    = selector;
    idt[num].zero        = 0;
    idt[num].type_attr   = flags;
}

void idt_load() {
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;
    __asm__ volatile ("lidt (%0)" : : "r" (&idtp));
}

void idt_init() {

    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8e);

    idt_load();
}