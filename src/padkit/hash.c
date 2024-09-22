/**
 * @file hash.c
 * @brief Implements the famous HASH33/djb2 algorithm.
 * @author Yavuz Koroglu
 */
#include "padkit/hash.h"

uint32_t hash32_str(char const str[static 1], size_t n) {
    uint32_t hash = UINT32_C(5381);
    while (n--) hash += (hash << 5) + (uint32_t)(*(str++));
    return hash;
}

uint64_t hash64_str(char const str[static 1], size_t n) {
    uint64_t hash = UINT64_C(5381);
    while (n--) hash += (hash << 5) + (uint64_t)(*(str++));
    return hash;
}
