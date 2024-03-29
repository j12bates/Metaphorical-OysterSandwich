#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PCI_CFG_ADDR 0x0CF8
#define PCI_CFG_DATA 0x0CFC

#define PCI_CFG_ADDR_ENABLE 1 << 31

#define PCI_CFG_VENDOR 0x00
#define PCI_CFG_DEVICE 0x02
#define PCI_CFG_COMMAND 0x04
#define PCI_CFG_STATUS 0x06

#define PCI_CFG_HEADER 0x0E
#define PCI_CFG_BAR0 0x10
#define PCI_CFG_INT 0x3C

#define PCI_CFG_COMMAND_IO 1 << 0
#define PCI_CFG_COMMAND_MEM 1 << 1
#define PCI_CFG_COMMAND_BUS_MASTER 1 << 2

#ifndef PCI_H
#define PCI_H

// PCI Configuration Operations
uint16_t pciConfig_read(uint16_t, uint8_t);
void pciConfig_write(uint16_t, uint8_t, uint16_t);

// Get Vendor/Device ID
uint32_t pciConfig_vendorDevice(uint16_t);

// Set Bus Mastering
void pciConfig_busMaster(uint16_t);

// Get IO Base Address
uint16_t pciConfig_ioBase(uint16_t);

// Get Interrupt Line
uint8_t pciConfig_intLine(uint16_t);

#endif
