// ACK: musl
#ifndef C_TOOLBELT_BYTESWAP_H
#define C_TOOLBELT_BYTESWAP_H

#include <stdint.h>

#define CTB_BSWAP16(x) (uint16_t)((uint16_t)(x) << 8 | (uint16_t)(x) >> 8)

#define CTB_BSWAP32(x)                                                         \
    (uint32_t)((uint32_t)(x) >> 24 | ((uint32_t)(x) >> 8 & 0xff00) |           \
               ((uint32_t)(x) << 8 & 0xff0000) | (uint32_t)(x) << 24)

#define CTB_BSWAP64(x)                                                         \
    (uint64_t)((CTB_BSWAP32((uint64_t)(x)) + 0ULL) << 32 |                     \
               CTB_BSWAP32((uint64_t)(x) >> 32))

static inline uint16_t ctb_bswap16(uint16_t x) { return CTB_BSWAP16(x); }

static inline uint32_t ctb_bswap32(uint32_t x) { return CTB_BSWAP32(x); }

static inline uint64_t ctb_bswap64(uint64_t x) { return CTB_BSWAP64(x); }

#endif
