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
     */
    uint_fast64_t hash_str(char const* restrict str, size_t register n);
#endif
