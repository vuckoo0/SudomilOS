#include "isr.h"
#include "../drivers/screen/screen.h"

void isr0_handler() {
    putstr("\nDivide by zero!");
    for (;;) { __asm__ volatile ("hlt"); }
}