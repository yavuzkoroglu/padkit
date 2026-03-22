/**
 * @file hash.h
 * @brief String hashing functions.
 * @author Yavuz KÖROĞLU
 * @see The DJB2 Hash Function.
 * @todo Add support for 128-bit hash values.
 */
#ifndef PADKIT_MISC_HASH_H
    #define PADKIT_MISC_HASH_H
    #include <stddef.h>
    #include <stdint.h>

    /**
     * @brief Computes a 32-bit hash value of a given string of <tt>n</tt> bytes.
     * @param str A pointer to the constant string.
     * @param n The number of bytes.
     * @returns A 32-bit unsigned integer as the hash value.
     * @see The DJB2 Hash Function.
     */
    uint32_t hash32_str(char const* str, size_t n);

    /**
     * @brief Computes a 64-bit hash value of a given string of <tt>n</tt> bytes.
     * @param str A pointer to the constant string.
     * @param n The number of bytes.
     * @returns A 64-bit unsigned integer as the hash value.
     * @see The DJB2 Hash Function.
     */
    uint64_t hash64_str(char const* str, size_t n);
#endif
