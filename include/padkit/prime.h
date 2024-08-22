/**
 * @file prime.h
 * @brief Defines some functions regarding prime numbers.
 * @author Yavuz Koroglu
 */
#ifndef PRIME_H
    #define PRIME_H
    #include <stdint.h>

    /**
     * @brief Checks if a given odd number is prime.
     *
     * @param[in] odd_x A constant 32-bit unsigned integer (must be odd and > 2).
     *
     * @return A Boolean value.
     */
    bool isPrime(uint32_t const odd_x);

    /**
     * @brief Finds the smallest prime number greater than or equal to x.
     *
     * @param[in] x A constant 32-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t nextPrime(uint32_t const x);
#endif
