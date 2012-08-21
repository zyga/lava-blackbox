#include "time-utils.h"


__attribute__((const))
struct timeval
timeval_delta(
    struct timeval start,
    struct timeval end
    )
{
    struct timeval result;
    const suseconds_t usec_per_sec = 1000000;
    /* If the minor component of the 'end' is smaller than the minor component
     * of the start do a subtraction with borrow. */
    if (end.tv_usec < start.tv_usec) {
        /* Since start.tv_usec is larger, first substract it from the full
         * second value Then add the smaller value end.tv_usec. This way we
         * will never have negative values here (time_t _should_ signed but
         * let's play it safe) and things will never overflow the usec_per_sec
         * value (1M microseconds). */
        result.tv_usec = (usec_per_sec - start.tv_usec) + end.tv_usec;
        /* Since we've borrowed one second to make the calculations above,
         * let's take account of that here */
        result.tv_sec = end.tv_sec - start.tv_sec - 1;
    } else {
        result.tv_usec = end.tv_usec - start.tv_usec;
        result.tv_sec = end.tv_sec - start.tv_sec;
    }
    return result;
}
