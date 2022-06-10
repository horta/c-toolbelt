#ifndef C_TOOLBELT_ENDIAN_H
#define C_TOOLBELT_ENDIAN_H

#include "c_toolbelt/export.h"
#include <stdint.h>

uint16_t ctb_htons(uint16_t);
uint32_t ctb_htonl(uint32_t);
uint64_t ctb_htonll(uint64_t);

uint16_t ctb_ntohs(uint16_t);
uint32_t ctb_ntohl(uint32_t);
uint64_t ctb_ntohll(uint64_t);

#endif
