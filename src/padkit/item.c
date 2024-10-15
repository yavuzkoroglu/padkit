#include <assert.h>
#include <string.h>
#include "padkit/hash.h"
#include "padkit/item.h"
#include "padkit/size.h"

uint32_t hash32_item(Item const* const item) {
    assert(isValid_item(item));
    return hash32_str((char const*)item->p, item->sz);
}

uint64_t hash64_item(Item const* const item) {
    assert(isValid_item(item));
    return hash64_str((char const*)item->p, item->sz);
}

bool isValid_item(void const* const p_item) {
    Item const* const item = (Item const*)p_item;

    if (item == NULL)               return 0;
    if (item->p == NULL)            return 0;
    if (item->sz == 0)              return 0;
    if (item->sz >= SZ32_MAX)       return 0;
    if (item->offset >= SZ32_MAX)   return 0;

    return 1;
}

Item* iterateNext_item(Item* const item) {
    assert(isValid_item(item));
    item->p = (char*)item->p + item->sz;
    return item;
}

Item* iteratePrev_item(Item* const item) {
    assert(isValid_item(item));
    item->p = (char*)item->p - item->sz;
    return item;
}
