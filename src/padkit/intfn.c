#include "padkit/intfn.h"
#include "padkit/swap.h"

uint32_t gcd(uint32_t a, uint32_t b) {
    if (a == 0 || b == 0) {
        return a | b;
    } else {
        uint32_t k = 0;
        while (IS_EVEN_I(a) && IS_EVEN_I(b)) {
            a >>= 1;
            b >>= 1;
            k++;
        }
        while (IS_EVEN_I(a)) a >>= 1;
        do {
            while (IS_EVEN_I(b)) b >>= 1;
            if (a > b) swap(&a, &b, sizeof(uint32_t));
        } while ((b = (b - a) >> 1));
        return a << k;
    }
}

bool isPrime(uint32_t const x) {
    /* UINT16_MAX is the largest integer whose square fits into 32 bits */
    uint32_t n = x > UINT16_MAX ? UINT16_MAX : x;

    if (x == 1) return 0;
    if (IS_EVEN_I(x)) return (x == 2);

    /* Find the largest n <= sqrt(x). */
    while (n > x / n) n >>= 1;
    while (n < UINT16_MAX && n * n < x) n++;

    /* Try all numbers n s.t. 2 < n <= sqrt(x). */
    for (n -= IS_EVEN_I(n); n > 2; n -= 2)
        if (x % n == 0) return 0;

    /* At this point, x has to be prime. */
    return 1;
}

uint32_t nextPrime(uint32_t const x) {
    /* Ensure the candidate being an odd number larger than 1. */
    uint32_t candidate = x + IS_EVEN_I(x) + 2*(isPrime(x) && IS_ODD_I(x));
    if (candidate == 1) return 2;

    /* Check all odd numbers and search for a prime number. */
    /* If candidate is UINT32_MAX, the next candidate is 1, which will raise an assertion failure. */
    while (!isPrime(candidate)) candidate += 2;

    return candidate;
}
