#ifndef __TTY_H
#define __TTY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
Default TTYs:
1. ttyD0: E9 Port
2. ttyS0-7: Serial ports COM1 to COM8
2. tty0-9: framebuffers 0 to 9 idk how to do this tho
*/

typedef void (*putchar_func)(char c);

#define TTY_FLAG_ENABLED 0x01
#define TTY_FLAG_SERIAL 0x02
#define TTY_FLAG_GRAPHICAL 0x04
#define TTY_FLAG_OTHER 0x08
#define TTY_FLAG_READONLY 0x16

typedef struct tty {
  char *name; // like ttyS0 or tty1 null terminated
  uint8_t id;
  putchar_func putchar;
  uint8_t flags;
} tty_t;

extern tty_t current_tty;

extern tty_t ttys[255]; // 255 because uint8_t id

int init_tty(uint8_t ident, char *name, putchar_func putc_func, uint8_t flags);

int unload_tty(uint8_t ident);
int switch_tty(uint8_t ident);

int output_on_tty(uint8_t ident, char c);
void outstr_tty(const char *message);
void outc_tty(char c);

#endif // __TTY_H