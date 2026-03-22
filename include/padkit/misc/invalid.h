/**
 * @file invalid.h
 * @brief Macros for invalid integer types.
 * @todo Add support for 128-bit integers.
 */
#ifndef PADKIT_MISC_INVALID_H
    #define PADKIT_MISC_INVALID_H
    #include <limits.h>
    #include <stdint.h>

    #ifndef INVALID_INT
        /**
         * @brief An integer value denoting an invalid integer.
         */
        #define INVALID_INT INT_MAX
    #endif

    #ifndef INVALID_INT8
        /**
         * @brief An 8-bit integer value denoting an invalid 8-bit integer.
         */
        #define INVALID_INT8 INT8_MAX
    #endif

    #ifndef INVALID_INT16
        /**
         * @brief A 16-bit integer value denoting an invalid 16-bit integer.
         */
        #define INVALID_INT16 INT16_MAX
    #endif

    #ifndef INVALID_INT32
        /**
         * @brief A 32-bit integer value denoting an invalid 32-bit integer.
         */
        #define INVALID_INT32 INT32_MAX
    #endif

    #ifndef INVALID_INT64
        /**
         * @brief A 64-bit integer value denoting an invalid 64-bit integer.
         */
        #define INVALID_INT64 INT64_MAX
    #endif

    #ifndef INVALID_SIZE
        /**
         * @brief A <tt>size_t</tt> value denoting an invalid <tt>size_t</tt>.
         */
        #define INVALID_SIZE SIZE_MAX
    #endif

    #ifndef INVALID_UINT
        /**
         * @brief An unsigned integer value denoting an invalid unsigned integer.
         */
        #define INVALID_UINT UINT_MAX
    #endif

    #ifndef INVALID_UINT8
        /**
         * @brief An 8-bit unsigned integer value denoting an invalid 8-bit unsigned integer.
         */
        #define INVALID_UINT8 UINT8_MAX
    #endif

    #ifndef INVALID_UINT16
        /**
         * @brief A 16-bit unsigned integer value denoting an invalid 16-bit unsigned integer.
         */
        #define INVALID_UINT16 UINT16_MAX
    #endif

    #ifndef INVALID_UINT32
        /**
         * @brief A 32-bit unsigned integer value denoting an invalid 32-bit unsigned integer.
         */
        #define INVALID_UINT32 UINT32_MAX
    #endif

    #ifndef INVALID_UINT64
        /**
         * @brief A 64-bit unsigned integer value denoting an invalid 64-bit unsigned integer.
         */
        #define INVALID_UINT64 UINT64_MAX
    #endif
#endif
