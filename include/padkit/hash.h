/**
 * @file hash.h
 * @brief Defines a string hash function.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_HASH_H
    #define PADKIT_HASH_H
    #include <stddef.h>
    #include <stdint.h>

    /**
     * @brief Computes the hash value of a string.
     * @param[in] str A non-null pointer to at least one constant character.
     * @param[in]   n A 64-bit unsigned integer.
     *
     * @return An unsigned integer capable of holding 64-bit values.
     */
    uint_fast64_t hash_str(char const str[static 1], uint64_t n);
#endif
