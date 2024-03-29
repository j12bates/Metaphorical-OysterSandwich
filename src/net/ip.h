#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rtl.h"

// Encode IP Address in Network Byte Order

#define IPV4(a, b, c, d) \
    a | \
    b << 8 | \
    c << 16 | \
    d << 24

#define IP_FRAGFLAG_DF 1 << 6

#ifndef IP_H
#define IP_H

// IP Address
typedef uint32_t ipv4Addr;

// Our Configuration
extern ipv4Addr ipv4_addr;
extern ipv4Addr ipv4_subMask;
extern ipv4Addr ipv4_gate;

// Protocols
enum Protocol {
    ICMP = 1,
    UDP = 17,
    IP_NONE = 0xFF
};

// Send a Packet
int ipv4_send(ipv4Addr, enum Protocol, char *, uint16_t);

// Handle a Packet
void ipv4_handle(macAddr, uint16_t);

// Get IP Address
ipv4Addr ipv4_getAddr(ipv4Addr);

// Copy Packet Payload
uint16_t ipv4_copy(char *, uint16_t);

// Calculate IP Checksum
uint16_t ip_checksum(uint16_t *, uint16_t);

#endif
