#include "ctb/endian.h"

#include <arpa/inet.h>
#include <stdbool.h>

#ifndef htonll
#if CTB_BYTE_ORDER == CTB_BIG_ENDIAN

static inline uint64_t htonll(uint64_t x) { return x; }
static inline uint64_t ntohll(uint64_t x) { return x; }

#else

static inline uint64_t htonll(uint64_t x) { return __builtin_bswap64(x); }
static inline uint64_t ntohll(uint64_t x) { return __builtin_bswap64(x); }

#endif
#endif

uint16_t ctb_htons(uint16_t x) { return htons(x); }
uint32_t ctb_htonl(uint32_t x) { return htonl(x); }
uint64_t ctb_htonll(uint64_t x) { return htonll(x); }

uint16_t ctb_ntohs(uint16_t x) { return ntohs(x); }
uint32_t ctb_ntohl(uint32_t x) { return ntohl(x); }
uint64_t ctb_ntohll(uint64_t x) { return ntohll(x); }
