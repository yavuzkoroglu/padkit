#ifndef PADKIT_SIZE_H
    #define PADKIT_SIZE_H
    #include <stdint.h>

    #define SZSZ_MAX        (SIZE_MAX >> 1)
    #define SZPTRDIFF_MAX   (PTRDIFF_MAX >> 1)

    #if UINT32_MAX < SIZE_MAX
        #define SZ32_MAX    INT32_MAX
    #else
        #define SZ32_MAX    SZSZ_MAX
    #endif

    #if UINT64_MAX < SIZE_MAX
        #define SZ64_MAX    INT64_MAX
    #else
        #define SZ64_MAX    SZSZ_MAX
    #endif
#endif
