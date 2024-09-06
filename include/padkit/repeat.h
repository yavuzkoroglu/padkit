#ifndef PADKIT_REPEAT_H
    #define PADKIT_REPEAT_H

    #define REPEAT(n) REPEAT_CNTR(_dcntr, n)

    #define REPEAT_CNTR(_dcntr, n) \
        for (unsigned long long _dcntr = (unsigned long long)(n); _dcntr--;)
#endif
