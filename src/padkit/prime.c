/**
 * @file prime.c
 * @brief Implements the functions defined in prime.h.
 * @author Yavuz Koroglu
 */
#include "padkit/debug.h"
#include "padkit/prime.h"

bool isPrime(uint32_t const odd_x) {
    DEBUG_ERROR_IF(odd_x % 2 == 0)
    DEBUG_ERROR_IF(odd_x == 1)

    /* Find the largest n <= sqrt(odd_x). */
    uint32_t register n = odd_x;
    while (n > odd_x / n) n >>= 1;
    while (n * n < odd_x) n++;

    /* Try all numbers n s.t. 2 < n <= sqrt(odd_x). */
    for (n -= !(n % 2); n > 2; n -= 2)
        if (odd_x % n == 0) return 0;

    /* At this point, odd_x has to be prime. */
    return 1;
}

uint32_t nextPrime(uint32_t const x) {
    DEBUG_ERROR_IF(x <= 2)

    /* Ensure the candidate being an odd number. */
    uint32_t candidate = x + !(x % 2);

    /* Check all odd numbers and search for a prime number. */
    while (!isPrime(candidate)) candidate += 2;

    /* candidate may overflow. In that case, return x. */
    if (candidate < x) return x;

    return candidate;
}
