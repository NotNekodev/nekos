#include "serial.h"
#include <stdint.h>

void outstr(uint16_t port, const char *message) {
  while (*message) {
    outb(port, (uint8_t)*message);
    if (*message == '\n') {
      outb(0x3F8, '\r');
    }
    message++;
  }
}

void outc(uint16_t port, char c) {
  outb(port, (uint8_t)c);
  if (c == '\n') {
    outb(port, '\r');
  }
}

void outc_com1(char c) { outc(COM1, c); }

int init_serial(uint16_t port) {
  outb(port + 1, 0x00); // Disable all interrupts
  outb(port + 3, 0x80); // Enable DLAB (set baud rate divisor)
  outb(port + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
  outb(port + 1, 0x00); //                  (hi byte)
  outb(port + 3, 0x03); // 8 bits, no parity, one stop bit
  outb(port + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  outb(port + 4, 0x0B); // IRQs enabled, RTS/DSR set
  outb(port + 4, 0x1E); // Set in loopback mode, test the serial chip
  outb(port + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial
                        // returns same byte)

  if (inb(port + 0) != 0xAE) {
    return 1;
  }

  outb(port + 4, 0x0F);
  return 0;
}
