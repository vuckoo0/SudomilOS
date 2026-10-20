#ifndef _PORTS_H_
#define _PORTS_H_

#include <stdint.h>

static inline uint8_t port_read(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

static inline void port_write(uint16_t port, uint8_t data) {
    __asm__ volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

#endif