#include "keyboard.h"
#include "../../cpu/pic.h"
#include "../../cpu/ports.h"
#include "../screen/screen.h"
#include "stdint.h"

#define KEYBOARD_DATA_PORT 0x60

static char scancode_to_ascii[] = {
    0,   0,  '1', '2', '3', '4', '5', '6',   // 0x00-0x07
   '7', '8', '9', '0', '-', '=',  0,   0,   // 0x08-0x0f
   'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',   // 0x10-0x17
   'o', 'p', '[', ']', '\n',  0, 'a', 's',   // 0x18-0x1f
   'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',   // 0x20-0x27
   '\'', '`',  0, '\\', 'z', 'x', 'c', 'v',  // 0x28-0x2f
   'b', 'n', 'm', ',', '.', '/',  0,   0,    // 0x30-0x37
    0,  ' '                                   // 0x38-0x39 (alt, space)
};

void irq1_handler() {

    uint8_t scancode = port_read(KEYBOARD_DATA_PORT);

    if (scancode & 0x80) {
        pic_send_eoi(1);
        return;
    }

    if (scancode < sizeof(scancode_to_ascii)) {
        char c = scancode_to_ascii[scancode];
        if (c != 0) {
            putc(c);
        }
    }

    pic_send_eoi(1);
}