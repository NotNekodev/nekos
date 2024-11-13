#ifndef __CPU_H
#define __CPU_H

#include <stdint.h>

struct task_state_segment {
  uint32_t reserved_0;
  uint64_t rsp0;
  uint64_t rsp1;
  uint64_t rsp2;
  uint64_t reserved_1;
  uint64_t ist1;
  uint64_t ist2;
  uint64_t ist3;
  uint64_t ist4;
  uint64_t ist5;
  uint64_t ist6;
  uint64_t ist7;
  uint64_t reserved_2;
  uint16_t reserved_3;
  uint16_t iomba;
};

static inline uint64_t read_msr(uint32_t reg) {
  uint32_t eax = 0, edx = 0;
  __asm__ volatile("rdmsr" : "=a"(eax), "=d"(edx) : "c"(reg) : "memory");
  return ((uint64_t)eax | (uint64_t)edx << 32);
}

static inline void write_msr(uint32_t reg, uint64_t value) {
  __asm__ volatile("wrmsr"
                   :
                   : "a"((uint32_t)value), "d"((uint32_t)(value >> 32)),
                     "c"(reg)
                   : "memory");
}

#endif // __CPU_H