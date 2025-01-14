#include "interrupt.h"

idtEntry_t idtEntries[IDT_ENTRY_COUNT];
idtPointer_t idtPointer;
extern uint64_t isrTable[];

struct stackFrame {
  struct stackFrame *rbp;
  uint64_t rip;
};

void stack_trace(uint64_t rbp, uint64_t rip) {
  struct stackFrame *stack = (struct stackFrame *)rbp;
  while (stack) {
    stack = stack->rbp;
  }
}

extern void iretq_asm(void);

irqHandler_t irqHandlers[IRQ_COUNT] = {0};

static const char *exceptionStrings[32] = {"Division By Zero",
                                           "Debug",
                                           "Nonmaskable Interrupt",
                                           "Breakpoint",
                                           "Overflow",
                                           "Bound Range Exceeded",
                                           "Invalid Opcode",
                                           "Device Not Available",
                                           "Double Fault",
                                           "Coprocessor Segment Overrun",
                                           "Invalid TSS",
                                           "Segment Not Present",
                                           "Stack Segment Fault",
                                           "General Protection Fault",
                                           "Page Fault",
                                           "Reserved",
                                           "x87 FPU Error",
                                           "Alignment Check",
                                           "Machine Check",
                                           "Simd Exception",
                                           "Virtualization Exception",
                                           "Control Protection Exception",
                                           "Reserved",
                                           "Reserved",
                                           "Reserved",
                                           "Reserved",
                                           "Reserved",
                                           "Reserved",
                                           "Hypervisor Injection Exception",
                                           "VMM Communication Exception",
                                           "Security Exception",
                                           "Reserved"};

void idt_set_gate(idtEntry_t idt[], int num, uint64_t base, uint16_t sel,
                  uint8_t flags) {
  idt[num].offsetLow = (base & 0xFFFF);
  idt[num].offsetMiddle = (base >> 16) & 0xFFFF;
  idt[num].offsetHigh = (base >> 32) & 0xFFFFFFFF;
  idt[num].selector = sel;
  idt[num].ist = 0;
  idt[num].flags = flags;
  idt[num].zero = 0;
}

void init_idt() {
  idtPointer.limit = sizeof(idtEntry_t) * IDT_ENTRY_COUNT - 1;
  idtPointer.base = (uintptr_t)&idtEntries;

  for (size_t i = 0; i < IRQ_COUNT; i++) {
    irqHandlers[i] = NULL;
  }

  for (int i = 0; i < 32; ++i) {
    idt_set_gate(idtEntries, i, isrTable[i], 0x08, 0x8E);
  }

  for (int i = IRQ_BASE; i < IRQ_BASE + IRQ_COUNT; ++i) {
    idt_set_gate(idtEntries, i, isrTable[i], 0x08, 0x8E);
  }

  idt_set_gate(idtEntries, 0x80, (uint64_t)isrTable[0x80], 0x08, 0xEE);

  idt_load((uint64_t)&idtPointer);
}

void IdtExcpHandler(Context_t frame) { asm("hlt"); }