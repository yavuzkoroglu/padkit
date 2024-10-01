#include <assert.h>
#include "padkit/hash.h"

uint32_t hash32_str(char const* str, size_t n) {
    uint32_t hash = UINT32_C(5381);
    assert(str != NULL);
    while (n--) hash += (hash << 5) + (uint32_t)(*(str++));
    return hash;
}

uint64_t hash64_str(char const* str, size_t n) {
    uint64_t hash = UINT64_C(5381);
    assert(str != NULL);
    while (n--) hash += (hash << 5) + (uint64_t)(*(str++));
    return hash;
}
