#ifndef PADKIT_BLITERALS_H
    #define PADKIT_BLITERALS_H
    #include <stdint.h>

    #define B(b) (                                      \
        ((uint_fast8_t)(((b) / 10000000) % 2) << 7) |   \
        ((uint_fast8_t)(((b) / 1000000) % 2) << 6)  |   \
        ((uint_fast8_t)(((b) / 100000) % 2) << 5)   |   \
        ((uint_fast8_t)(((b) / 10000) % 2) << 4)    |   \
        ((uint_fast8_t)(((b) / 1000) % 2) << 3)     |   \
        ((uint_fast8_t)(((b) / 100) % 2) << 2)      |   \
        ((uint_fast8_t)(((b) / 10) % 2) << 1)       |   \
        ((uint_fast8_t)((b) % 2))                       \
    )

    #define B2(high,low) \
        (((uint_fast16_t)(high) << 8U) | (uint_fast16_t)(low))

    #define B4(hh,h,l,ll) \
        (((uint_fast32_t)B2(hh,h) << 16U) | (uint_fast32_t)B2(l,ll))

    #define B8(hhhh,hhh,hh,h,l,ll,lll,llll) \
        (((uint_fast64_t)B4(hhhh,hhh,hh,h) << 32U) | (uint_fast64_t)B4(l,ll,lll,llll))
#endif
