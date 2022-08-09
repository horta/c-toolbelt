#include "ctb/ctb.h"
#include <stdio.h>

union u16
{
    uint16_t u;
    uint8_t d[2];
};

union u32
{
    uint32_t u;
    uint8_t d[4];
};

union u64
{
    uint64_t u;
    uint8_t d[8];
};

static int assert_be16(union u16 v)
{
    if (v.d[0] != 0x01) return 1;
    if (v.d[1] != 0x23) return 1;
    return 0;
}

static int assert_le16(union u16 v)
{
    if (v.d[1] != 0x01) return 1;
    if (v.d[0] != 0x23) return 1;
    return 0;
}

static int assert_be32(union u32 v)
{

    if (v.d[0] != 0x01) return 1;
    if (v.d[1] != 0x23) return 1;
    if (v.d[2] != 0x45) return 1;
    if (v.d[3] != 0x67) return 1;
    return 0;
}

static int assert_le32(union u32 v)
{

    if (v.d[3] != 0x01) return 1;
    if (v.d[2] != 0x23) return 1;
    if (v.d[1] != 0x45) return 1;
    if (v.d[0] != 0x67) return 1;
    return 0;
}

static int assert_be64(union u64 v)
{

    if (v.d[0] != 0x01) return 1;
    if (v.d[1] != 0x23) return 1;
    if (v.d[2] != 0x45) return 1;
    if (v.d[3] != 0x67) return 1;
    if (v.d[4] != 0x89) return 1;
    if (v.d[5] != 0xAB) return 1;
    if (v.d[6] != 0xCD) return 1;
    if (v.d[7] != 0xEF) return 1;
    return 0;
}

static int assert_le64(union u64 v)
{

    if (v.d[7] != 0x01) return 1;
    if (v.d[6] != 0x23) return 1;
    if (v.d[5] != 0x45) return 1;
    if (v.d[4] != 0x67) return 1;
    if (v.d[3] != 0x89) return 1;
    if (v.d[2] != 0xAB) return 1;
    if (v.d[1] != 0xCD) return 1;
    if (v.d[0] != 0xEF) return 1;
    return 0;
}

int main(void)
{
    {
        union u16 v = {.u = 0x0123};
#if CTB_BYTE_ORDER == CTB_BIG_ENDIAN
        if (assert_be16(v)) return 1;
#else
        if (assert_le16(v)) return 1;
#endif
    }

    {
        union u32 v = {.u = 0x01234567};
#if CTB_BYTE_ORDER == CTB_BIG_ENDIAN
        if (assert_be32(v)) return 1;
#else
        if (assert_le32(v)) return 1;
#endif
    }

    {
        union u64 v = {.u = 0x0123456789ABCDEF};
#if CTB_BYTE_ORDER == CTB_BIG_ENDIAN
        if (assert_be64(v)) return 1;
#else
        if (assert_le64(v)) return 1;
#endif
    }

    {
        union u16 v = {.u = 0x0123};
        v.u = CTB_HTONS(v.u);
        if (assert_be16(v)) return 1;
    }

    {
        union u32 v = {.u = 0x01234567};
        v.u = CTB_HTONL(v.u);
        if (assert_be32(v)) return 1;
    }

    {
        union u64 v = {.u = 0x0123456789ABCDEF};
        v.u = CTB_HTONLL(v.u);
        if (assert_be64(v)) return 1;
    }

    return 0;
}
