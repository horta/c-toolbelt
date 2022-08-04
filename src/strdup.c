#include "ctb/strdup.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *strdup(char const *s)
{
    size_t l = strlen(s);
    char *d = malloc(l + 1);
    if (!d) return NULL;
    return memcpy(d, s, l + 1);
}
