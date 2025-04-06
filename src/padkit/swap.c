#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "padkit/memalloc.h"
#include "padkit/size.h"
#include "padkit/swap.h"

void swap(void* const p1, void* const p2, size_t const sz) {
    assert(p1 != NULL);
    assert(p2 != NULL);
    assert(sz > 0);

    if (sz >= SZSZ_MAX) {
        MALLOC_ERROR
    } else if (sz == 1) {
        uint8_t tmp     = *(uint8_t*)p1;
        *(uint8_t*)p1   = *(uint8_t*)p2;
        *(uint8_t*)p2   = tmp;
    } else if (sz == 2) {
        uint16_t tmp    = *(uint16_t*)p1;
        *(uint16_t*)p1  = *(uint16_t*)p2;
        *(uint16_t*)p2  = tmp;
    } else if (sz == 3) {
        uint32_t tmp    = *(uint32_t*)p1;
        *(uint32_t*)p1  = *(uint32_t*)p2;
        *(uint32_t*)p2  = tmp;
    } else if (sz == 4) {
        uint64_t tmp    = *(uint64_t*)p1;
        *(uint64_t*)p1  = *(uint64_t*)p2;
        *(uint64_t*)p2  = tmp;
    } else {
        void* const p3  = mem_alloc(sz);
        memcpy(p3, p1, sz);
        memcpy(p1, p2, sz);
        memcpy(p2, p3, sz);
        free(p3);
    }
}
