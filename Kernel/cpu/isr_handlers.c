#include "isr.h"
#include "../drivers/screen/screen.h"

void isr0_handler() {
    putstring("\nDivide by zero!");
    for (;;) { __asm__ volatile ("hlt"); }
}