/* Acknowledgement: safec libc extension */
#include "ctb/strtok_s.h"

#include <errno.h>
#include <limits.h>
#include <stddef.h>

#ifndef ESNULLP
#define ESNULLP 400 /* null ptr */
#endif

#ifndef ESZEROL
#define ESZEROL 401 /* length is zero */
#endif

#ifndef ESUNTERM
#define ESUNTERM 407 /* unterminated string */
#endif

/*
 * The spec does not call out a maximum len for the strtok src
 * string (the max delims size), so one is defined here.
 */
#ifndef STRTOK_DELIM_MAX_LEN
#define STRTOK_DELIM_MAX_LEN 16
#endif

char *ctb_strtok_s(char *restrict str, size_t *restrict strmax,
                   const char *restrict delim, char **restrict ptr)
{
    const char *pt = 0;
    char *ptoken = 0;
    size_t dlen = 0;
    size_t slen = 0;

    if (strmax == 0)
    {
        errno = ESNULLP;
        return 0;
    }
    if (*strmax == 0)
    {
        errno = ESZEROL;
        return 0;
    }
    if (delim == 0)
    {
        errno = ESNULLP;
        return 0;
    }
    if (ptr == 0)
    {
        errno = ESNULLP;
        return 0;
    }

    /* if the source was 0, use the tokenizer context */
    if (str == 0)
    {
        str = *ptr;
        if (str == 0)
        {
            errno = ESNULLP;
            return 0;
        }
    }

    /*
     * scan dest for a delimiter
     */
    dlen = *strmax;
    ptoken = 0;
    errno = 0;
    while (*str != '\0' && !ptoken)
    {
        if (dlen == 0)
        {
            *ptr = 0;
            errno = ESUNTERM;
            return 0;
        }

        /*
         * must scan the entire delimiter list
         * ISO should have included a delimiter string limit!!
         */
        slen = STRTOK_DELIM_MAX_LEN;
        pt = delim;
        while (*pt != '\0')
        {

            if (slen == 0)
            {
                *ptr = 0;
                *strmax = 0;
                *str = '\0';
                errno = ESUNTERM;
                return 0;
            }
            slen--;

            if (*str == *pt)
            {
                ptoken = 0;
                break;
            }
            else
            {
                pt++;
                ptoken = str;
            }
        }
        str++;
        dlen--;
    }

    /*
     * if the beginning of a token was not found, then no
     * need to continue the scan.
     */
    if (ptoken == 0)
    {
        *strmax = dlen;
        return ptoken;
    }

    /*
     * Now we need to locate the end of the token
     */
    while (*str != '\0')
    {

        if (dlen == 0)
        {
            *ptr = 0;
            *strmax = 0;
            *str = '\0';
            errno = ESUNTERM;
            return 0;
        }

        slen = STRTOK_DELIM_MAX_LEN;
        pt = delim;
        while (*pt != '\0')
        {

            if (slen == 0)
            {
                *ptr = 0;
                *strmax = 0;
                *str = '\0';
                errno = ESUNTERM;
                return 0;
            }
            slen--;

            if (*str == *pt)
            {
                /*
                 * found a delimiter, set to null
                 * and return context ptr to next char
                 */
                *str = '\0';
                *ptr = (str + 1);   /* return pointer for next scan */
                *strmax = dlen - 1; /* account for the nulled delimiter */
                return ptoken;
            }
            else
            {
                /*
                 * simply scanning through the delimiter string
                 */
                pt++;
            }
        }
        str++;
        dlen--;
    }

    *strmax = dlen;
    return ptoken;
}
