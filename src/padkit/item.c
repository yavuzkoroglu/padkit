#include <assert.h>
#include <string.h>
#include "padkit/hash.h"
#include "padkit/item.h"
#include "padkit/size.h"

bool areEquiv_item(
    Item const i1,
    Item const i2
) {
    assert(isValid_item(i1));
    assert(isValid_item(i2));

    return i1.sz == i2.sz && memcmp(i1.p, i2.p, i1.sz) == 0;
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
    if (item.p == NULL)             return 0;
    if (item.sz == 0)               return 0;
    if (item.sz >= SZ32_MAX)        return 0;
    if (item.offset >= SZ32_MAX)    return 0;

    return 1;
}
