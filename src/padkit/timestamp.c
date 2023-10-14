/**
 * @file timestamp.c
 * @brief Implements the functions in timestamp.h
 * @see timestamp.h
 * @author Yavuz Koroglu
 */
#include <time.h>
#include "padkit/timestamp.h"

char const* get_timestamp(void) {
    static char ts[18];
    time_t const curtime = time(NULL);
    struct tm* const ltm = localtime(&curtime);
    #ifndef NDEBUG
        if (strftime(ts, sizeof(ts), "%x %X", ltm) != sizeof(ts) - 1)
            return NULL;
    #else
        strftime(ts, sizeof(ts), "%x %X", ltm);
    #endif
    return ts;
}
