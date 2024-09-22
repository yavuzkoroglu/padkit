#ifndef PADKIT_REPEAT_H
    #define PADKIT_REPEAT_H
    #include <stdint.h>

    #define REPEAT(n)               REPEAT_CNTR(r_dcntr, n)
    #define REPEAT_CNTR(r_dcntr, n) for (uintmax_t r_dcntr = (uintmax_t)(n); r_dcntr--;)
#endif
