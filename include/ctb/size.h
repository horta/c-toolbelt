#ifndef C_TOOLBELT_SIZE_H
#define C_TOOLBELT_SIZE_H

#define __CTB_MEMBER_REF(var, member) ((__typeof__(var) *)0)->member

#define CTB_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define CTB_SIZEOF_MEMBER(var, member) sizeof(__CTB_MEMBER_REF((var), member))
#define CTB_ARRAY_SIZEOF(var, member)                                          \
    CTB_ARRAY_SIZE(__CTB_MEMBER_REF((var), member))

#endif
