/**
 * @file timestamp.c
 * @brief Implements the functions in timestamp.h
 * @see timestamp.h
 * @author Yavuz Koroglu
 */
#include <time.h>
#include "padkit/timestamp.h"

char const* get_timestamp(void) {
    static char timebuffer[18];
    time_t const curtime = time(NULL);
    #ifndef NDEBUG
        if (strftime(timebuffer, sizeof(timebuffer), "%x %X", localtime(&curtime)) != 17)
            return NULL;
    #else
        strftime(timebuffer, sizeof(timebuffer), "%x %X", localtime(&curtime));
    #endif
    return timebuffer;
}
