#ifndef C_TOOLBELT_ENDIAN_H
#define C_TOOLBELT_ENDIAN_H

#include "ctb/byteswap.h"
#include "ctb/config.h"
#include "ctb/export.h"
#include <arpa/inet.h>
#include <stdint.h>

CTB_API uint16_t ctb_htons(uint16_t);
CTB_API uint32_t ctb_htonl(uint32_t);
CTB_API uint64_t ctb_htonll(uint64_t);

CTB_API uint16_t ctb_ntohs(uint16_t);
CTB_API uint32_t ctb_ntohl(uint32_t);
CTB_API uint64_t ctb_ntohll(uint64_t);

#if CTB_BYTE_ORDER == CTB_BIG_ENDIAN
#define CTB_HTONS(x) (uint16_t)(x)
#define CTB_HTONL(x) (uint32_t)(x)
#define CTB_HTONLL(x) (uint64_t)(x)
#else
#define CTB_HTONS(x) CTB_BSWAP16((uint16_t)(x))
#define CTB_HTONL(x) CTB_BSWAP32((uint32_t)(x))
#define CTB_HTONLL(x) CTB_BSWAP64((uint64_t)(x))
#endif

#endif
