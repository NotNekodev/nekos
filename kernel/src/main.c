#include <limine.h>
#include <limine/requests.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <dev/serial.h>
#include <dev/tty.h>

#include <arch/x86_64/gdt.h>
#include <arch/x86_64/interrupts/interrupt.h>

__attribute__((
    used, section(".limine_requests"))) static volatile LIMINE_BASE_REVISION(3);

static void hcf(void) {
  for (;;) {
    asm("hlt");
  }
}

void kmain(void) {
  if (LIMINE_BASE_REVISION_SUPPORTED == false) {
    hcf();
  }

  if (framebuffer_request.response == NULL ||
      framebuffer_request.response->framebuffer_count < 1) {
    hcf();
  }

  struct limine_framebuffer *framebuffer =
      framebuffer_request.response->framebuffers[0];

  init_serial(COM1);

  init_tty(0, "ttyS0", outc_com1, TTY_FLAG_ENABLED | TTY_FLAG_SERIAL);
  switch_tty(0);

  outstr_tty("Test from the tty system on ttyS0!\n");

  init_gdt();
  init_idt();

  hcf();
}
