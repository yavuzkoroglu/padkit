#ifndef PADKIT_BLITERALS_H
    #define PADKIT_BLITERALS_H
    #include <stdint.h>

    /* https://stackoverflow.com/questions/2611764/can-i-use-a-binary-literal-in-c-or-c/78961030#78961030 */
    #define B(b) (                                                                                      \
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

    #define BIT(b, i)                   (uint_fast8_t)!!(#b[i]-'0')
    #define B2(b1,b0)                   (((uint_fast16_t)B(b1)<<8)|(uint_fast16_t)B(b0))
    #define B4(b3,b2,b1,b0)             (((uint_fast32_t)B2(b3,b2)<<16)|(uint_fast32_t)B2(b1,b0))
    #define B8(b7,b6,b5,b4,b3,b2,b1,b0) (((uint_fast64_t)B4(b7,b6,b5,b4)<<32)|(uint_fast64_t)B4(b3,b2,b1,b0))
#endif
