/**
 * @file hash.c
 * @brief Implements the famous HASH33/djb2 algorithm.
 * @author Yavuz Koroglu
 */
#include "padkit/hash.h"

uint_fast64_t hash_str(char const str[static 1], uint64_t n) {
    register uint_fast64_t hash = UINT64_C(5381);
    while (n-- && *str) hash += (hash << 5) + (uint_fast64_t)(*(str++));
    return hash;
}
