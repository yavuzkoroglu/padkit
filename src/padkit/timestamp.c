/**
 * @file timestamp.c
 * @brief Implements the functions in timestamp.h
 * @see timestamp.h
 * @author Yavuz Koroglu
 */
#include <time.h>
#include "padkit/debug.h"
#include "padkit/timestamp.h"

char const* get_timestamp(void) {
    static char ts[TS_LEN + 1];
    time_t const curtime = time(nullptr);
    struct tm* const ltm = localtime(&curtime);

    DEBUG_ASSERT(strftime(ts, sizeof(ts), TS_FMT, ltm) == sizeof(ts) - 1)
    NDEBUG_EXECUTE(strftime(ts, sizeof(ts), TS_FMT, ltm))

    return ts;
}
