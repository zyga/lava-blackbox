#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <sys/time.h>

/**
 * Function for computing delta of two struct timeval values.
 **/
__attribute__((const))
struct timeval
timeval_delta(
    struct timeval start,
    struct timeval end
    );

#endif
