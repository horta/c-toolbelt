#include "c_toolbelt/endian.h"

#include <arpa/inet.h>
#include <stdbool.h>

#if __APPLE__
#include <machine/endian.h>
#else
#include <endian.h>
#endif

#if BYTE_ORDER != LITTLE_ENDIAN && BYTE_ORDER != BIG_ENDIAN
#error We are supporting little and big endian only for now.
#endif

#ifndef htonll

#ifndef BYTE_ORDER
#define BYTE_ORDER __BYTE_ORDER__
#endif

#ifndef BIG_ENDIAN
#define BIG_ENDIAN __BIG_ENDIAN__
#endif

#if BYTE_ORDER == BIG_ENDIAN

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
