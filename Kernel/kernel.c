#include "drivers/screen/screen.h"
#include "cpu/idt.h"
#include "cpu/pic.h"

void main() {

    screenclr();
    pic_remap();
    idt_init();
    pic_unmask(1);
    __asm__ volatile ("sti");

    putstr("$ ");

    for (;;) {}
}