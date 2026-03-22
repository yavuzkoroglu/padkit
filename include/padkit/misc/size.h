/**
 * @file size.h
 * @brief Macros that define maximum sizes for containers.
 * @author Yavuz KÖROĞLU
 * @todo Add support for 128-bit size values.
 */
#ifndef PADKIT_MISC_SIZE_H
    #define PADKIT_MISC_SIZE_H
    #include <stdint.h>

    #ifndef SZSZ_MAX
        /**
         * @brief The maximum valid value of a <tt>size_t</tt>.
         * @important This value fits into a <tt>ssize_t</tt> variable.
         */
        #define SZSZ_MAX (SIZE_MAX >> 1)
    #endif

    #ifndef SZPTRDIFF_MAX
        /**
         * @brief The maximum valid value of a <tt>ptrdiff_t</tt>.
         */
        #define SZPTRDIFF_MAX (PTRDIFF_MAX >> 1)
    #endif

    /**
     * @def SZ32_MAX
     * @brief The maximum valid value of a 32-bit size value.
     */
    #ifndef SZ32_MAX
        #if UINT32_MAX < SIZE_MAX
            #define SZ32_MAX INT32_MAX
        #else
            #define SZ32_MAX SZSZ_MAX
        #endif
    #endif

    /**
     * @def SZ64_MAX
     * @brief The maximum valid value of a 64-bit size value.
     */
    #ifndef SZ64_MAX
        #if UINT64_MAX < SIZE_MAX
            #define SZ64_MAX INT64_MAX
        #else
            #define SZ64_MAX SZSZ_MAX
        #endif
    #endif
#endif
