#include "int.h"
#include "pic.h"

#include "../mem/mem.h"

// IDT will be held here
__attribute__((aligned(0x10)))
struct {
    uint16_t isr_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isr_high;
} __attribute__((packed)) idt[256];

// IDT Register Structure
IDTRegister idtr = {
    .base = (uint32_t) &idt,
    .limit = sizeof(idt) - 1
};

// Encode IDT Entry
static void int_encodeIDTEntry(uint8_t target, uint32_t isr_base, bool trap)
{
    // Encode ISR Base Address
    idt[target].isr_low = isr_base & 0xFFFF;
    idt[target].isr_high = isr_base >> 16 & 0xFFFF;

    // Use Code Segment
    idt[target].selector = MEM_SEG_CODE;

    // Set Gate Type
    idt[target].attributes = 
        INT_IDT_ATTR_PR | 
        (trap ? INT_IDT_GATE_TRAP : INT_IDT_GATE_INT)
    ;

    // Clear Reserved Bits
    idt[target].reserved = 0;
}

// Initialize Interrupts
void int_init(void)
{
    // Send all Exceptions here
    for (int i = 0; i < 32; i++) {
        int_encodeIDTEntry(i, (uint32_t) &ex, false);
    }

    // Load the IDT
    asm volatile (
        "lidt %0; sti" : :
        "m"(idtr)
    );

    // Initialize PIC
    pic_init();
}

// Set up an IRQ
void int_setupIRQ(uint8_t line, uint32_t isr_base)
{
    // Interrupt Number
    line &= 0xF;
    uint8_t target =
        line < 8 ?
        PIC0_OFFSET + line :
        PIC1_OFFSET + line - 8
    ;

    // Make IDT Entry
    int_encodeIDTEntry(target, isr_base, false);

    // Set Interrupt Mask
    pic_maskIRQ(line, true);
}

// End Interrupt
void int_end(uint8_t line)
{
    // Send EOI to PIC
    pic_sendEOI(line);
}

// Enable/Disable Interrupts
void int_enable(void)
{
    asm ("sti");
}

void int_disable(void)
{
    asm ("cli");
}
