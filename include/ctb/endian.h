#ifndef C_TOOLBELT_ENDIAN_H
#define C_TOOLBELT_ENDIAN_H

#include "ctb/config.h"
#include "ctb/export.h"
#include <stdint.h>

CTB_API uint16_t ctb_htons(uint16_t);
CTB_API uint32_t ctb_htonl(uint32_t);
CTB_API uint64_t ctb_htonll(uint64_t);

CTB_API uint16_t ctb_ntohs(uint16_t);
CTB_API uint32_t ctb_ntohl(uint32_t);
CTB_API uint64_t ctb_ntohll(uint64_t);

// ACK: Darwin
#define CTB_LITTLE_ENDIAN 1234
#define CTB_BIG_ENDIAN 4321

#endif
