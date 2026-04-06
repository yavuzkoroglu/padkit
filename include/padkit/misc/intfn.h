/**
 * @file intfn.h
 * @brief Integer-related macros and functions.
 * @author Yavuz KÖROĞLU
 * @todo Add support for 128-bit integers.
 */
#ifndef PADKIT_MISC_INTFN_H
    #define PADKIT_MISC_INTFN_H
    #include <stdbool.h>
    #include <stdint.h>

    /**
     * @brief Takes the absolute value of an 8-bit integer and converts it to <tt>uint8_t</tt>.
     * @param a An 8-bit integer.
     * @returns The absolute value of <tt>a</tt> as <tt>uint8_t</tt>.
     */
    #define ABS_I8(a) ((uint8_t)(((a) > 0) ? (a) : (-a)))

    /**
     * @brief Takes the absolute value of a 16-bit integer and converts it to <tt>uint16_t</tt>.
     * @param a A 16-bit integer.
     * @returns The absolute value of <tt>a</tt> as <tt>uint16_t</tt>.
     */
    #define ABS_I16(a) ((uint16_t)(((a) > 0) ? (a) : (-a)))

    /**
     * @brief Takes the absolute value of a 32-bit integer and converts it to <tt>uint32_t</tt>.
     * @param a A 32-bit integer.
     * @returns The absolute value of <tt>a</tt> as <tt>uint32_t</tt>.
     */
    #define ABS_I32(a) ((uint32_t)(((a) > 0) ? (a) : (-a)))

    /**
     * @brief Takes the absolute value of a 64-bit integer and converts it to <tt>uint64_t</tt>.
     * @param a A 64-bit integer.
     * @returns The absolute value of <tt>a</tt> as <tt>uint64_t</tt>.
     */
    #define ABS_I64(a) ((uint64_t)(((a) > 0) ? (a) : (-a)))

    /**
     * @brief Computes a Boolean value about the evenness of a given integer.
     * @param a An integer.
     * @returns <tt>1</tt> if <tt>a</tt> is even, <tt>0</tt> otherwise.
     * @see <tt>IS_ODD_I(a)</tt>.
     */
    #define IS_EVEN_I(a) !IS_ODD_I(a)

    /**
     * @brief Computes a Boolean value about the oddness of a given integer.
     * @param a An integer.
     * @returns <tt>1</tt> if <tt>a</tt> is odd, <tt>0</tt> otherwise.
     */
    #define IS_ODD_I(a) ((a) & 1)

    /**
     * @brief Computes maximum of two given integers.
     * @param a The first integer.
     * @param b The second integer.
     * @returns <tt>a</tt> if <tt>a > b</tt>, <tt>b</tt> otherwise.
     */
    #define MAX_I(a,b) (((a) > (b)) ? (a) : (b))

    /**
     * @brief Computes minimum of two given integers.
     * @param a The first integer.
     * @param b The second integer.
     * @returns <tt>a</tt> if <tt>a < b</tt>, <tt>b</tt> otherwise.
     */
    #define MIN_I(a,b) (((a) < (b)) ? (a) : (b))

    /**
     * @brief Computes the largest 32-bit unsigned integer <tt>y</tt> s.t. <tt>2^y <= x</tt>.
     * @param x A 32-bit unsigned integer.
     * @returns <tt>floor(log2(x))</tt> as a 32-bit unsigned integer.
     * @pre <tt>x</tt> is non-zero.
     */
    uint32_t floorLog2(uint32_t x);

    /**
     * @brief Computes the largest 32-bit unsigned integer <tt>y</tt> s.t. <tt>y^2 <= x_sq</tt>.
     * @param x_sq A 32-bit unsigned integer.
     * @returns <tt>floor(sqrt(x_sq))</tt> as a 32-bit unsigned integer.
     */
    uint32_t floorSqrt(uint32_t const x_sq);

    /**
     * @brief Computeso the greatest common divisor (gcd) of two 32-bit unsigned integers.
     * @param a The first 32-bit unsigned integer.
     * @param b The second 32-bit unsigned integer.
     * @returns <tt>gcd(a, b)</tt> as a 32-bit unsigned integer.
     */
    uint32_t gcd(uint32_t a, uint32_t b);

    /**
     * @brief Computes a Boolean value about the primeness of a given 32-bit unsigned integer.
     * @param x A 32-bit unsigned integer.
     * @returns <tt>1</tt> if <tt>x</tt> is prime, <tt>0</tt> otherwise.
     * @see <tt>floorSqrt(x)</tt>.
     */
    bool isPrime(uint32_t const x);

    /**
     * @brief Computes the the smallest prime number larger than a given 32-bit integer.
     * @param x A 32-bit unsigned integer.
     * @returns The smallest prime number larger than <tt>x</tt> as a 32-bit unsigned integer.
     * @see <tt>isPrime(x)</tt>.
     * @important If <tt>x</tt> is larger than the largest 32-bit prime number, this function returns <tt>3</tt>.
     */
    uint32_t nextPrime(uint32_t const x);
#endif
