/**
 * @file repeat.h
 * @brief Macros for repeating type control flow loops.
 * @author Yavuz KÖROĞLU
 */
#ifndef PADKIT_MISC_REPEAT_H
    #define PADKIT_MISC_REPEAT_H
    #include <stdint.h>

    /**
     * @brief Repeats the following statement(s) \c n times.
     * @param n The # of repeats.
     * @warning Cannot have nested <tt>REPEAT(n)</tt> loops because they all use the same counter variable.
     */
    #define REPEAT(n) REPEAT_CNTR(r_dcntr, n)

    /**
     * @brief Repeats the following statement(s) \c n times and uses a given down counter.
     * @param r_dcntr The name of the down counter variable.
     * @param n The # of repeats.
     * @important Allows nested repeating type loops.
     */
    #define REPEAT_CNTR(r_dcntr, n) for (uintmax_t r_dcntr = (uintmax_t)(n); r_dcntr--;)
#endif
