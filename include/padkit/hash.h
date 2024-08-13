/**
 * @file hash.h
 * @brief Defines a string hash function.
 * @author Yavuz Koroglu
 */
#ifndef HASH_H
    #define HASH_H
    #include <stddef.h>
    #include <stdint.h>

    /**
     * @brief Computes the hash value of a string.
     * @param str The string.
     * @param n The string length.
     */
    uint_fast64_t hash_str(char const* restrict str, uint64_t register n);
#endif
