#include <stdarg.h>
#include <stdio.h>
#include "padkit/timestamp.h"
#include "padkit/verbose.h"

bool verbose = VERBOSE_DEFAULT;

/* https://stackoverflow.com/questions/36120717/correcting-format-string-is-not-a-string-literal-warning#36120843 */
__attribute__((__format__ (__printf__, 1, 0)))
int printf_verbose(char const* const restrict format, ...) {
    if (verbose) {
        va_list args;
        char const* const p_timestamp = get_timestamp();
        va_start(args, format);
        printf("[%s] - ", p_timestamp);
        {
            int const n = vprintf(format, args);
            va_end(args);
            puts("");
            return n;
        }
    } else {
        return 0;
    }
}
