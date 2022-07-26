#ifndef C_TOOLBELT_STRLCPY_H
#define C_TOOLBELT_STRLCPY_H

#include "c_toolbelt/export.h"
#include "c_toolbelt/size.h"
#include <stddef.h>

/*
 * Copy string src to buffer dst of size dsize. At most dsize-1
 * chars will be copied.  Always NUL terminates (unless dsize == 0).
 * Returns strlen(src); if retval >= dsize, truncation occurred.
 */
CTB_API size_t ctb_strlcpy(char *dst, const char *src, size_t dsize);

#define CTB_STRLCPY(ptr, dst, src)                                             \
    ctb_strlcpy((ptr)->dst, src, CTB_ARRAY_SIZEOF(*(ptr), dst))

#endif
