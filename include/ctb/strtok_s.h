#ifndef C_TOOLBELT_STRTOK_H_H
#define C_TOOLBELT_STRTOK_H_H

#include "ctb/export.h"
#include <stddef.h>

CTB_API char *ctb_strtok_s(char *restrict str, size_t *restrict strmax,
                           const char *restrict delim, char **restrict ptr);

#endif
