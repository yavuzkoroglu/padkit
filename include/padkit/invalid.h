#ifndef PADKIT_INVALID_H
    #define PADKIT_INVALID_H
    #include <limits.h>
    #include <stdint.h>

    #ifndef INVALID_INT
        #define INVALID_INT         INT_MAX
    #endif

    #ifndef INVALID_INT8
        #define INVALID_INT8        INT8_MAX
    #endif

    #ifndef INVALID_INT16
        #define INVALID_INT16       INT16_MAX
    #endif

    #ifndef INVALID_INT32
        #define INVALID_INT32       INT32_MAX
    #endif

    #ifndef INVALID_INT64
        #define INVALID_INT64       INT64_MAX
    #endif

    #ifndef INVALID_SIZE
        #define INVALID_SIZE        SIZE_MAX
    #endif

    #ifndef INVALID_UINT
        #define INVALID_UINT        UINT_MAX
    #endif

    #ifndef INVALID_UINT8
        #define INVALID_UINT8       UINT8_MAX
    #endif

    #ifndef INVALID_UINT16
        #define INVALID_UINT16      UINT16_MAX
    #endif

    #ifndef INVALID_UINT32
        #define INVALID_UINT32      UINT32_MAX
    #endif

    #ifndef INVALID_UINT64
        #define INVALID_UINT64      UINT64_MAX
    #endif
#endif
