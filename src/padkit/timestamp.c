#include <assert.h>
#include <time.h>
#include "padkit/timestamp.h"

char const* get_timestamp(void) {
    static char ts[TS_LEN + 1];
    time_t const curtime = time(NULL);
    struct tm* const ltm = localtime(&curtime);

    #ifndef NDEBUG
        size_t const ts_len = strftime(ts, sizeof(ts), TS_FMT, ltm);
        assert(ts_len == TS_LEN);
    #else
        strftime(ts, sizeof(ts), TS_FMT, ltm);
    #endif

    return ts;
}
