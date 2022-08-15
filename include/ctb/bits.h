#ifndef C_TOOLBELT_BITS_H
#define C_TOOLBELT_BITS_H

#include <stdbool.h>

static inline void ctb_bits_clr(unsigned long *x, unsigned bit)
{
    *x &= ~(1UL << bit);
}

static inline bool ctb_bits_get(unsigned long *x, unsigned bit)
{
    return !!((*x >> bit) & 1UL);
}

static inline void ctb_bits_set(unsigned long *x, unsigned bit)
{
    *x |= 1UL << bit;
}

static inline void ctb_bits_flp(unsigned long *x, unsigned bit)
{
    *x ^= 1UL << bit;
}

static inline unsigned ctb_bits_ffs(unsigned long *x)
{
    return *x ? (unsigned)(__builtin_ffsl(*x) - 1) : sizeof(long);
}

#endif
