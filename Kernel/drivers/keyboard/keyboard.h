#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>

#define KEYBOARD_DATA_PORT 0x60
#define INPUT_BUFFER_SIZE 1024

void irq1_handler(void);

char readchar();\
void readstring(char* buf, uint32_t len);

#endif