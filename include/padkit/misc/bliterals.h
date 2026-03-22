/**
 * @file bliterals.h
 * @brief Macros for binary literals.
 * @author Yavuz KÖROĞLU
 * @see https://stackoverflow.com/questions/2611764/can-i-use-a-binary-literal-in-c-or-c/78961030#78961030
 * @warning Supports binary literals up to 64 bits.
 * @todo Add support for 128-bit integers.
 */
#ifndef PADKIT_MISC_BLITERALS_H
    #define PADKIT_MISC_BLITERALS_H
    #include <stdint.h>

    /**
     * @brief Computes the <tt>uint8_t</tt> value of an 8-bit binary literal.
     * @param b The binary literal, e.g., <tt>01011</tt>.
     * @returns The <tt>uint8_t</tt> value of <tt>b</tt>, e.g, <tt>MKB(01011) = 11</tt>.
     * @warning Use <tt>B(b)</tt> if <tt>b</tt> is a macro that should expand first to a binary literal.
     * @warning If <tt>b</tt> has fewer than 8 bits, enough trailing zeros added to the left.
     * @warning If <tt>b</tt> has more than 8 bits, only the \b leftmost 8 bits are considered.
     */
    #define MKB(b) (                                                                                    \
        sizeof(#b) <= 1                                                                                 \
        ? BIT(0,0)                                                                                      \
        : sizeof(#b) == 2                                                                               \
        ? BIT(b,0)                                                                                      \
        : sizeof(#b) == 3                                                                               \
        ? BIT(b,0)<<1|BIT(b,1)                                                                          \
        : sizeof(#b) == 4                                                                               \
        ? BIT(b,0)<<2|BIT(b,1)<<1|BIT(b,2)                                                              \
        : sizeof(#b) == 5                                                                               \
        ? BIT(b,0)<<3|BIT(b,1)<<2|BIT(b,2)<<1|BIT(b,3)                                                  \
        : sizeof(#b) == 6                                                                               \
        ? BIT(b,0)<<4|BIT(b,1)<<3|BIT(b,2)<<2|BIT(b,3)<<1|BIT(b,4)                                      \
        : sizeof(#b) == 7                                                                               \
        ? BIT(b,0)<<5|BIT(b,1)<<4|BIT(b,2)<<3|BIT(b,3)<<2|BIT(b,4)<<1|BIT(b,5)                          \
        : sizeof(#b) == 8                                                                               \
        ? BIT(b,0)<<6|BIT(b,1)<<5|BIT(b,2)<<4|BIT(b,3)<<3|BIT(b,4)<<2|BIT(b,5)<<1|BIT(b,6)              \
        : BIT(b,0)<<7|BIT(b,1)<<6|BIT(b,2)<<5|BIT(b,3)<<4|BIT(b,4)<<3|BIT(b,5)<<2|BIT(b,6)<<1|BIT(b,7)  \
    )

    /**
     * @brief Computes the \a ith bit of a binary literal, from the left.
     * @param b The binary literal, e.g., <tt>01011</tt>.
     * @param i The bit index, e.g., <tt>2</tt>.
     * @returns \a ith bit of <tt>b</tt>, e.g. <tt>"01011"[2] = 0</tt>.
     */
    #define BIT(b,i) (uint8_t)!!(#b[i]-'0')

    /**
     * @brief Computes the <tt>uint8_t</tt> value of a binary literal.
     * @param b The binary literal, e.g., <tt>01011</tt>. Can be at most 8 bits long.
     * @returns The <tt>uint8_t</tt> value of <tt>b</tt>, e.g, <tt>B(01011) = 11</tt>.
     * @important Always prefer <tt>B(b)</tt> instead of <tt>MKB(b)</tt>.
     */
    #define B(b) MKB(b)

    /**
     * @brief Computes the <tt>uint16_t</tt> value of the concatenation of two 8-bit binary literals.
     * @param b1 The leftmost binary literal.
     * @param b0 The rightmost binary literal.
     * @returns The \c uint16_t value of <tt>b1b0</tt>, e.g. <tt>B2(00001111,00000001) = 3841</tt>.
     */
    #define B2(b1,b0) (((uint16_t)B(b1)<<8)|(uint16_t)B(b0))

    /**
     * @brief Computes the <tt>uint32_t</tt> value of the concatenation of four 8-bit binary literals.
     * @param b3 The leftmost binary literal.
     * @param b2 The second binary literal from the left.
     * @param b1 The third binary literal from the left.
     * @param b0 The rightmost binary literal.
     * @returns The <tt>uint32_t</tt> value of <tt>b3b2b1b0</tt>.
     */
    #define B4(b3,b2,b1,b0) (((uint32_t)B2(b3,b2)<<16)|(uint32_t)B2(b1,b0))

    /**
     * @brief Computes the <tt>uint64_t</tt> value of the concatenation of eight 8-bit binary literals.
     * @param b7 The leftmost binary literal.
     * @param b6 The second binary literal from the left.
     * @param b5 The third binary literal from the left.
     * @param b4 The fourth binary literal from the left.
     * @param b3 The fifth binary literal from the left.
     * @param b2 The sixth binary literal from the left.
     * @param b1 The seventh binary literal from the left.
     * @param b0 The rightmost binary literal.
     * @returns The <tt>uint64_t</tt> value of <tt>b7b6b5b4b3b2b1b0</tt>.
     */
    #define B8(b7,b6,b5,b4,b3,b2,b1,b0) (((uint64_t)B4(b7,b6,b5,b4)<<32)|(uint64_t)B4(b3,b2,b1,b0))
#endif
