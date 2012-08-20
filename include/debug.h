#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

/**
 * Enable debuging and redirect all debug messages to the specified stream
 **/
void
debug_enable(
    FILE *stream
    );

/**
 * Emit a printf-like message on the debug channel
 **/
void
debug_log(
    const char *format, ...
    ) __attribute__((format(printf, 1, 2)));

#endif
