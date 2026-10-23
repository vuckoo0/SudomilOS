#include "keyboard.h"
#include "../../cpu/pic.h"
#include "../../cpu/ports.h"
#include "../screen/screen.h"
#include "stdint.h"

static char scancode_to_ascii[] = {
    0,   0,  '1', '2', '3', '4', '5', '6',   // 0x00-0x07
   '7', '8', '9', '0', '-', '=',  '\b',   0,   // 0x08-0x0f
   'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',   // 0x10-0x17
   'o', 'p', '[', ']', '\n',  0, 'a', 's',   // 0x18-0x1f
   'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',   // 0x20-0x27
   '\'', '`',  0, '\\', 'z', 'x', 'c', 'v',  // 0x28-0x2f
   'b', 'n', 'm', ',', '.', '/',  0,   0,    // 0x30-0x37
    0,  ' '                                   // 0x38-0x39 (alt, space)
};

static char input_buffer[INPUT_BUFFER_SIZE];
static uint32_t input_buffer_head = 0;
static uint32_t input_buffer_tail = 0;

static void buffer_push(char c) {
    uint32_t next = (input_buffer_head + 1) % INPUT_BUFFER_SIZE;
    if (next == input_buffer_tail) {return;}
    input_buffer[input_buffer_head] = c;
    input_buffer_head = next;
}

static uint8_t buffer_is_empty() {
    return input_buffer_head == input_buffer_tail;
}

static char buffer_pop() {
    if (buffer_is_empty()) {return 0;}
    char c = input_buffer[input_buffer_tail];
    input_buffer_tail = (input_buffer_tail + 1) % INPUT_BUFFER_SIZE;
    return c;
}

void irq1_handler() {

    uint8_t scancode = port_read(KEYBOARD_DATA_PORT);

    if (scancode & 0x80) {
        pic_send_eoi(1);
        return;
    }

    if (scancode < sizeof(scancode_to_ascii)) {
        char c = scancode_to_ascii[scancode];
        if (c != 0) {
            putchar(c);
            buffer_push(c);
        }
    }

    pic_send_eoi(1);
}

char readchar() {

    while (buffer_is_empty()) {
        __asm__ volatile ("hlt");
    }

    return buffer_pop();
}

void readstring(char* buf, uint32_t len) {

    uint32_t i = 0;

    while (1) {

        char current_char = readchar();

        if (current_char == '\n') {
            buf[i] = '\0';
            putchar('\n');
            return;
        }

        if (current_char == '\b') {
            if (i > 0) {
                i--;
                putchar('\b');
            }

            continue;
        }

        if (i < len - 1) {
            buf[i] = current_char;
            i++;
        }
    }
}