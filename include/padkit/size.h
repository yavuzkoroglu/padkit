/**
 * @file size.h
 * @brief Defines size related macros.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_SIZE_H
    #define PADKIT_SIZE_H
    #include <stdint.h>

    /**
     * @def SZSZ_MAX
     *   The largest valid size for a size variable.
     */
    #define SZSZ_MAX        (SIZE_MAX >> 1)

    /**
     * @def SZ32_MAX
     *   The largest valid size for a 32-bit unsigned integer.
     */
    #if UINT32_MAX < SIZE_MAX
        #define SZ32_MAX    INT32_MAX
    #else
        #define SZ32_MAX    SZSZ_MAX
    #endif

    /**
     * @def SZ64_MAX
     *   The largest valid size for a 64-bit unsigned integer.
     */
    #if UINT64_MAX < SIZE_MAX
        #define SZ64_MAX    INT64_MAX
    #else
        #define SZ64_MAX    SZSZ_MAX
    #endif
#endif
