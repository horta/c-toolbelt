#include "ctb/bzero.h"
#include <string.h>

void ctb_bzero(void *dst, size_t dsize) { memset(dst, 0, dsize); }
