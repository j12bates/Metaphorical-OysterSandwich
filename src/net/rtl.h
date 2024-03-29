#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Min/Max Transfer Unit

#define RTL_MTU 1500
#define RTL_MIN 46

// Register I/O Addresses

#define RTL_ID0 0x00

#define RTL_TSD0 0x10
#define RTL_TSAD0 0x20
#define RTL_RBSTART 0x30

#define RTL_CAPR 0x38
#define RTL_CBR 0x3A

#define RTL_IMR 0x3C
#define RTL_ISR 0x3E

#define RTL_RCR 0x44

#define RTL_CR 0x37
#define RTL_CONFIG1 0x52

// Register Bitmasks

#define RTL_TSD_OWN 1 << 13
#define RTL_TSD_TOK 1 << 15
#define RTL_TSD_TABT 1 << 30

#define RTL_ISR_ROK 1 << 0
#define RTL_ISR_TOK 1 << 2
#define RTL_ISR_LINKCHG 1 << 5
#define RTL_ISR_SERR 1 < 15

#define RTL_RCR_AAP 1 << 0
#define RTL_RCR_APM 1 << 1
#define RTL_RCR_AM 1 << 2
#define RTL_RCR_AB 1 << 3
#define RTL_RCR_WRAP 1 << 7

#define RTL_CR_BUFE 1 << 0
#define RTL_CR_TE 1 << 2
#define RTL_CR_RE 1 << 3
#define RTL_CR_RST 1 << 4

// Receive Buffer

#define RTL_RECV_HDR 0
#define RTL_RECV_LEN 2
#define RTL_RECV_PACKET 4

#define RTL_PCI_VENDOR_DEVICE 0x813910EC
// #define RTL_PCI_ADDR 3 << 8 | 3 << 3 | 0
#define RTL_PCI_ADDR 0 << 8 | 3 << 3 | 0

#ifndef RTL_H
#define RTL_H

// MAC Address
typedef struct { uint8_t x[6]; } __attribute__((packed)) macAddr;
bool rtl_eqMacAddr(macAddr, macAddr);

extern macAddr rtl_macAddr;
extern const macAddr emptyAddr, broadcastAddr;

// Ether-type
enum EtherType {
    ETHER = 1,
    IPV4 = 0x0800,
    ARP = 0x0806
};

// Initialize
bool rtl_init(void);

// Transmit an Ethernet Frame
int rtl_transmit(char *, uint16_t, enum EtherType, macAddr);

// Copy Ethernet Frame Payload
void rtl_copy(uint16_t, char *, uint16_t);

// Handle an Interrupt
extern void rtl_isr(void);
void rtl_intHandler(void);

#endif
