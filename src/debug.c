#include "debug.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>


static bool debug_enabled = false;
static FILE *debug_stream = NULL;


void
debug_enable(
    FILE *stream
    )
{
    debug_stream = stream;
    debug_enabled = true;
}


void
__attribute__((format(printf, 1, 2)))
debug_log(
    const char *format, ...
    )
{
    va_list ap;
    va_start(ap, format);
    if (debug_enabled) {
        fprintf(debug_stream, "LAVA> ");
        vfprintf(debug_stream, format, ap);
    }
    va_end(ap);
}
