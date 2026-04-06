/**
 * @file verbose.h
 * @brief Printing functions conditional upon a Boolean \c verbose variable.
 * @author Yavuz KÖROĞLU
 */
#ifndef PADKIT_MISC_VERBOSE_H
    #define PADKIT_MISC_VERBOSE_H
    #include <stdbool.h>
    #include <stdio.h>

    #ifndef VERBOSE_DEFAULT
        /**
         * @brief Verbose is disabled by default.
         */
        #define VERBOSE_DEFAULT (0)
    #endif

    /** The global Boolean toggle for verbose operations. */
    extern bool verbose;

    /**
     * @brief Prints a formatted message to \c stdout with timestamp if \c verbose is \c true.
     * @param format A format string (usually a string literal).
     * @return Whatever the internal vprintf() call returns.
     * @important Always returns 0 if \c verbose is \c false.
     */
    int printf_verbose(char const* const restrict format, ...);

    /**
     * @brief Prints a formatted message to \c stdout with timestamp if \c verbose is \c true.
     * @param stream A constant pointer to a \c FILE stream.
     * @param format A format string (usually a string literal).
     * @return Whatever the internal vfprintf() call returns.
     * @important Always returns 0 if \c verbose is \c false.
     * @pre \c stream is nonnull.
     */
    int fprintf_verbose(FILE* const stream, char const* const restrict format, ...);
#endif
