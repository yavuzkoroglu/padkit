/**
 * @file repeat.h
 * @brief Defines the REPEAT macro.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_REPEAT_H
    #define PADKIT_REPEAT_H

    /**
     * @def REPEAT(n)
     *   Repeats the following code block or statement n times.
     */
    #define REPEAT(n) REPEAT_CNTR(_dcntr, n)

    /**
     * @def REPEAT_CNTR(_dcntr, n)
     *   A repeat control with a custom down counter name.
     */
    #define REPEAT_CNTR(_dcntr, n) \
        for (unsigned long long _dcntr = (unsigned long long)(n); _dcntr--;)
#endif
