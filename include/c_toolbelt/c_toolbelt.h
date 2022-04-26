#ifndef C_TOOLBELT_H
#define C_TOOLBELT_H

#include "c_toolbelt/export.h"
#include <stddef.h>

#define CTB_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/*
 * Copy string src to buffer dst of size dsize. At most dsize-1
 * chars will be copied.  Always NUL terminates (unless dsize == 0).
 * Returns strlen(src); if retval >= dsize, truncation occurred.
 */
CTB_API size_t ctb_strlcpy(char *dst, const char *src, size_t dsize);

#define CTB_STRLCPY(ptr, dst, src)                                             \
    ctb_strlcpy((ptr)->dst, src, __CTB_ARRAY_SIZE_OF(*(ptr), dst))

/* ------ PRIVATE MACROS ------ */
#define __CTB_MEMBER_REF(var, member) ((__typeof__(var) *)0)->member

#define __CTB_ARRAY_SIZE_OF(var, member)                                       \
    CTB_ARRAY_SIZE(__CTB_MEMBER_REF((var), member))

#endif
