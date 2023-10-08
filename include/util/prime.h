/**
 * @file prime.h
 * @brief Defines some functions regarding prime numbers.
 * @author Yavuz Koroglu
 */
#ifndef PRIME_H
    #define PRIME_H
    #include <stdbool.h>
    #include <stdint.h>

    /**
     * @brief Checks if a given odd number is prime.
     * @param odd_x An odd number greater than 1.
     */
    bool isPrime(uint32_t const odd_x);

    /**
     * @brief Finds the smallest prime number greater than or equal to x.
     * @param x A non-negative number.
     */
    uint32_t nextPrime(uint32_t const x);
#endif
