#include "screen.h"

volatile char* video_memory = (char*)0xb8000;

static int cursor_row = 0;
static int cursor_col = 0;

static void update_pointer() {
    video_memory = (char*)(0xb8000 + (cursor_row * 80 + cursor_col) * 2);
}


void putc(const char c) {

    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
    } else {
        video_memory[0] = c;
        video_memory[1] = 0x02;
        cursor_col++;
        if (cursor_col >= 80) {   // wrap at end of line
            cursor_col = 0;
            cursor_row++;
        }
    }
    
    update_pointer();
}

void putstr(const char *s) {
    
    int i = 0;
    while (1) {

        char current_char = s[i];

        if (current_char == '\0') {
            break;
        }

        putc(current_char);
        i += 1;
    }
}

void screenclr() {
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        char* vga = (char*)0xb8000;
        vga[i]     = ' ';
        vga[i + 1] = 0x02;
    }
    cursor_row = 0;
    cursor_col = 0;
    update_pointer();
}