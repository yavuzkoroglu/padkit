#include <assert.h>
#include "padkit/prime.h"

bool isPrime(uint32_t const odd_x) {
    /* UINT16_MAX is the largest integer whose square fits into 32 bits */
    register uint32_t n = odd_x > UINT16_MAX ? UINT16_MAX : odd_x;

    assert(odd_x % 2 == 1);
    assert(odd_x > 1);

    /* Find the largest n <= sqrt(odd_x). */
    while (n > odd_x / n) n >>= 1;
    while (n < UINT16_MAX && n * n < odd_x) n++;

    /* Try all numbers n s.t. 2 < n <= sqrt(odd_x). */
    for (n -= !(n % 2); n > 2; n -= 2)
        if (odd_x % n == 0) return 0;

    /* At this point, odd_x has to be prime. */
    return 1;
}

uint32_t nextPrime(uint32_t const x) {
    /* Ensure the candidate being an odd number larger than 1. */
    uint32_t candidate = x + !(x % 2);
    assert(x > 1);

    /* Check all odd numbers and search for a prime number. */
    /* If candidate is UINT32_MAX, the next candidate is 1, which will raise an assertion failure. */
    while (!isPrime(candidate)) candidate += 2;

    return candidate;
}
