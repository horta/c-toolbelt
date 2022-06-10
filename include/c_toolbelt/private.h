#ifndef C_TOOLBELT_PRIVATE_H
#define C_TOOLBELT_PRIVATE_H

#define __CTB_MEMBER_REF(var, member) ((__typeof__(var) *)0)->member

#define __CTB_ARRAY_SIZEOF(var, member)                                        \
    CTB_ARRAY_SIZE(__CTB_MEMBER_REF((var), member))

#endif
