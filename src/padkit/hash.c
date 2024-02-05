/**
 * @file hash.c
 * @brief Implements the famous HASH33/djb2 algorithm.
 * @author Yavuz Koroglu
 */
#include "padkit/debug.h"
#include "padkit/hash.h"

uint_fast64_t hash_str(char const* restrict str, size_t register n) {
    DEBUG_ERROR_IF(str == NULL)
    uint_fast64_t register hash = 5381;
    while (n-- && *str) hash += (hash << 5) + (uint_fast64_t)(*(str++));
    return hash;
}
