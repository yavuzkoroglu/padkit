#ifndef PADKIT_SIZE_H
    #define PADKIT_SIZE_H
    #include <stdint.h>

    #ifndef SZSZ_MAX
        #define SZSZ_MAX        (SIZE_MAX >> 1)
    #endif

    #ifndef SZPTRDIFF_MAX
        #define SZPTRDIFF_MAX   (PTRDIFF_MAX >> 1)
    #endif

    #ifndef SZ32_MAX
        #if UINT32_MAX < SIZE_MAX
            #define SZ32_MAX    INT32_MAX
        #else
            #define SZ32_MAX    SZSZ_MAX
        #endif
    #endif

    #ifndef SZ64_MAX
        #if UINT64_MAX < SIZE_MAX
            #define SZ64_MAX    INT64_MAX
        #else
            #define SZ64_MAX    SZSZ_MAX
        #endif
    #endif
#endif
