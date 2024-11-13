#ifndef __GDT_H
#define __GDT_H

#include <stdint.h>

#include "cpu.h"
#include "lock.h"

typedef struct {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_mid;
  uint8_t access_byte;
  uint8_t limit_high_and_flags;
  uint8_t base_high;
} __attribute__((packed)) segment_descriptor;

typedef struct {
  segment_descriptor descriptor;
  uint32_t base;
  uint32_t reserved;
} __attribute__((packed)) system_segment_descriptor;

void init_gdt();
void rld_gdt();
void rld_tss(struct task_state_segment *tss_addr);

#endif // __GDT_H