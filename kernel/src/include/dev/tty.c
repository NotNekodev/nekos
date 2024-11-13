#include "tty.h"
#include <stdint.h>

tty_t ttys[255];
tty_t current_tty;

int init_tty(uint8_t ident, char *name, putchar_func putc_func, uint8_t flags) {

  bool enabled = flags & TTY_FLAG_ENABLED;
  bool readonly = flags & TTY_FLAG_READONLY;

  int type = TTY_FLAG_OTHER;

  if (flags & TTY_FLAG_SERIAL) {
    type = TTY_FLAG_SERIAL;
  } else if (flags & TTY_FLAG_GRAPHICAL) {
    type = TTY_FLAG_GRAPHICAL;
  } else if (flags & TTY_FLAG_OTHER) {
    type = TTY_FLAG_OTHER;
  }

  if (sizeof(name) > 10) {
    return 1;
  }

  tty_t new_tty;
  new_tty.name = name;
  new_tty.id = ident;
  new_tty.putchar = putc_func;
  new_tty.flags = readonly | enabled | type;

  ttys[ident] = new_tty;

  return 0;
}

int unload_tty(uint8_t ident) {
  int status = init_tty(ident, ttys[ident].name, ttys[ident].putchar,
                        ttys[ident].flags & ~TTY_FLAG_ENABLED);
  if (status != 0) {
    return 1;
  }

  return 0;
}

int switch_tty(uint8_t ident) {
  current_tty = ttys[ident];
  return 0;
}

int output_on_tty(uint8_t ident, char c) {
  ttys[ident].putchar(c);
  return 0;
}

void outstr_tty(const char *message) {
  while (*message) {
    current_tty.putchar(*message);
    if (*message == '\n') {
      current_tty.putchar('\r');
    }
    message++;
  }
}

void outc_tty(char c) { current_tty.putchar(c); }