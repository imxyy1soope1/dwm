/* See LICENSE file for copyright and license details. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void
die(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    if (fmt[0] && fmt[strlen(fmt)-1] == ':') {
        fputc(' ', stderr);
        perror(NULL);
    } else {
        fputc('\n', stderr);
    }

    exit(1);
}

void *
ecalloc(size_t nmemb, size_t size)
{
    void *p;

    if (!(p = calloc(nmemb, size)))
        die("calloc:");
    return p;
}

char **
add_argument(char **original, char *opt_char, char *opt_arg, char *opt_name)
{
    int num_args;
    for (num_args = 0; original[num_args] != NULL; num_args++)
        ;
    char **result = ecalloc(num_args + 3, sizeof(char *));

    int write_index = 0;
    int skip_next = 0;
    for (int i = 0; i < num_args; ++i) {
        if (skip_next) {
            skip_next = 0;
            continue;
        }
        if (!strcmp(original[i], opt_char) ||
            (opt_name && !strcmp(original[i], opt_name))) {
            if (opt_arg)
                skip_next = 1;
            continue;
        }
        result[write_index++] = original[i];
    }

    result[write_index++] = opt_char;
    result[write_index] = opt_arg;

    return result;
}
