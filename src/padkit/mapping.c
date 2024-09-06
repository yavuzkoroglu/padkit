#include "padkit/mapping.h"
#include "padkit/size.h"

bool isValid_mppng(Mapping const mapping[static const 1]) {
    if (mapping->next_id >= SZ32_MAX) return 0;

    return 1;
}
