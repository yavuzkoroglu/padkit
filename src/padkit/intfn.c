#include <assert.h>
#include "padkit/intfn.h"
#include "padkit/swap.h"

uint32_t floor_log2(uint32_t x) {
    uint32_t log2_x = 0;
    assert(x != 0);
    while (x > 1) {
        x >>= 1;
        log2_x++;
    }
    return log2_x;
}

uint32_t floor_sqrt(uint32_t const x_sq) {
    uint32_t k, u, l, xh, xh_sq;

    if (x_sq == 0)
        return 0;

    k = floor_log2(x_sq) >> 1;
    l = 1 << k;
    u = l << 1;

    while ((u - l) > 1) {
        xh = (u + l) >> 1;
        xh_sq = xh * xh;
        if (xh_sq > x_sq)
            u = xh;
        else if (xh_sq < x_sq)
            l = xh;
        else
            return xh;
    }

    return l;
}

uint32_t gcd(uint32_t a, uint32_t b) {
    if (a == 0 || b == 0) {
        return a | b;                                   /* gcd(a, 0) = a AND gcd(0, b) = b */
    } else {
        uint32_t k = 0;
        while (IS_EVEN_I(a) && IS_EVEN_I(b)) {          /* gcd(2^k * a, 2^k * b) = 2^k * gcd(a, b) */
            a >>= 1;
            b >>= 1;
            k++;
        }
        while (IS_EVEN_I(a)) a >>= 1;                   /* gcd(2^l * a, b) = gcd(a, b) */
        do {
            while (IS_EVEN_I(b)) b >>= 1;               /* gcd(a, 2^l * b) = gcd(a, b) */
            if (a > b) swap(&a, &b, sizeof(uint32_t));  /* gcd(a, b) = gcd(b, a) */
        } while ((b -= a));                             /* gcd(a, b) = gcd(a, |b - a|) */

        return a << k;                                  /* gcd(2^k * a, 2^k * l * a) = 2^k * a */
    }
}

bool isPrime(uint32_t const x) {
    uint32_t n = floor_sqrt(x) + 1;

    if (x == 1) return 0;
    if (IS_EVEN_I(x)) return (x == 2);

    for (n -= IS_EVEN_I(n); n > 2; n -= 2)
        if (x % n == 0) return 0;

    return 1;
}

uint32_t nextPrime(uint32_t const x) {
    /* Ensure the candidate is an odd number larger than 1. */
    uint32_t candidate = x + IS_EVEN_I(x) + 2*(isPrime(x) && IS_ODD_I(x));
    if (candidate == 1) return 2;

    /* Check all odd numbers and search for a prime number. */
    while (!isPrime(candidate)) candidate += 2;

    return candidate;
}
