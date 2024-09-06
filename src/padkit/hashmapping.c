#include "padkit/hashmapping.h"
#include "padkit/size.h"

bool isValid_hmpng(HashMapping const mapping[static const 1]) {
    if (mapping->nextId >= SZ32_MAX) return 0;

    return 1;
}
