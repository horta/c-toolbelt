#include "ctb/realloc.h"

#include <assert.h>
#include <stdlib.h>

void *ctb_realloc(void *ptr, size_t size)
{
    assert(size > 0);
    void *new_ptr = realloc(ptr, size);

    if (!new_ptr) free(ptr);
    return new_ptr;
}
