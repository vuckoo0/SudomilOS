#include "drivers/screen/screen.h"
#include "drivers/keyboard/keyboard.h"
#include "cpu/idt.h"
#include "cpu/pic.h"

void main() {

    screenclr();
    pic_remap();
    idt_init();
    __asm__ volatile ("sti");

    while (1) {

        putstring("$ ");

        char username[32];
        readstring(username, 32);

        putstring(username);
        putchar('\n');
    }

}