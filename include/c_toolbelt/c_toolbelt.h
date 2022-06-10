#ifndef C_TOOLBELT_C_TOOLBELT_H
#define C_TOOLBELT_C_TOOLBELT_H

#include "c_toolbelt/endian.h"
#include "c_toolbelt/export.h"
#include "c_toolbelt/private.h"
#include "c_toolbelt/realloc.h"
#include "c_toolbelt/strlcpy.h"

#define CTB_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define CTB_SIZEOF_MEMBER(var, member) sizeof(__CTB_MEMBER_REF((var), member))

#endif
