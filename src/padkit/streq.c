/**
 * @file streq.c
 * @brief Implements the functions defined in streq.h.
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/debug.h"
#include "padkit/streq.h"

#ifdef __SIZEOF_INT128__
    typedef __uint128_t block_t __attribute((aligned(1)));
#else
    typedef unsigned long long block_t __attribute((aligned(1)));
#endif

bool mem_eq_n(char const a[static 1], char const b[static 1], size_t n) {
    size_t const remainder    = n & (sizeof(block_t) - 1);
    size_t const lshift_count = (sizeof(block_t) - remainder) << 3;
    block_t const* a_block    = (block_t const*)a;
    block_t const* b_block    = (block_t const*)b;
    DEBUG_ASSERT(n < SIZE_MAX >> 1)
    for (n /= sizeof(block_t); n; a_block++, b_block++, n--) if (*a_block != *b_block) return 0;
    return remainder == 0 || (*a_block << lshift_count) == (*b_block << lshift_count);
}

bool str_eq(char const a[static 1], char const b[static 1]) {
    for (; *a == *b; a++, b++) if (*a == '\0') return 1;
    return 0;
}

bool str_eq_n(char const a[static 1], char const b[static 1], size_t n) {
    DEBUG_ASSERT(n < SIZE_MAX >> 1)
    for (n--; *a == *b; a++, b++, n--) if (n == 0 || *a == '\0') return 1;
    return 0;
}

int strcmp_as_comparator(void const* needle, void const* haystack) {
    DEBUG_ERROR_IF(needle == NULL)
    DEBUG_ERROR_IF(haystack == NULL)
    {
        char const* const key = needle;
        char const* const candidate = ((char const* const* const)haystack)[0];
        return strcmp(key, candidate);
    }
}
