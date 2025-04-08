#ifndef PADKIT_INTFN_H
    #define PADKIT_INTFN_H
    #include <stdbool.h>
    #include <stdint.h>

    #define ABS_I8(a)        ((uint8_t)(((a) > 0) ? (a) : (-a)))
    #define ABS_I16(a)      ((uint16_t)(((a) > 0) ? (a) : (-a)))
    #define ABS_I32(a)      ((uint32_t)(((a) > 0) ? (a) : (-a)))
    #define ABS_I64(a)      ((uint64_t)(((a) > 0) ? (a) : (-a)))
    #define IS_EVEN_I(a)    !IS_ODD_I(a)
    #define IS_ODD_I(a)     ((a) & 1)
    #define MAX_I(a,b)      (((a) > (b)) ? (a) : (b))
    #define MIN_I(a,b)      (((a) < (b)) ? (a) : (b))

    uint32_t gcd(uint32_t a, uint32_t b);
    bool isPrime(uint32_t const odd_x);
    uint32_t nextPrime(uint32_t const x);
#endif
