#include <assert.h>
#include <string.h>
#include "padkit/hash.h"
#include "padkit/item.h"
#include "padkit/size.h"

bool areEquiv_item(
    Item const i1,
    Item const i2
) {
    // An implementation should NEVER call this function with invalid items.
    assert(isValid_item(i1));
    assert(isValid_item(i2));

    if (i1.sz != i2.sz)                     return 0;   // Two equal items must have the same size.
    if (i1.p == i2.p)                       return 1;   // Two items with the same pointer are equal.
    if (memcmp(i1.p, i2.p, i1.sz) == 0)     return 1;   // Finally, compare the two items byte-by-byte.

    return 0;
}

uint32_t hash32_item(Item const item) {
    assert(isValid_item(item));
    return hash32_str((char const*)item.p, item.sz);
}

uint64_t hash64_item(Item const item) {
    assert(isValid_item(item));
    return hash64_str((char const*)item.p, item.sz);
}

bool isValid_item(Item const item) {
    if (item.p == NULL)                     return 0;   // A NULL Item is invalid.
    if (item.sz >= SZ32_MAX)                return 0;   // An Item must have a reasonable size.
    if (item.offset >= SZ32_MAX)            return 0;   // An Item must have a reasonable offset.
    if (item.sz + item.offset >= SZ32_MAX)  return 0;   // The next Item must be able to have reasonable offset.

    return 1;
}
