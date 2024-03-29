#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define INT_IDT_ATTR_PR 1 << 7

#define INT_IDT_GATE_INT 0xE
#define INT_IDT_GATE_TRAP 0xF

#ifndef INT_H
#define INT_H

// IDT Register
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) IDTRegister;

extern IDTRegister idtr;

// Exception Handler
extern void ex(void);

// Initialization
void int_init(void);

// Set up an IRQ
void int_setupIRQ(uint8_t, uint32_t);

// End Interrupt
void int_end(uint8_t);

// Enable/Disable Interrupts
void int_enable(void);
void int_disable(void);

#endif
