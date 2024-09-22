#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "padkit/memalloc.h"
#include "padkit/size.h"

void* mem_alloc(size_t const sz) {
    assert(sz > 0);

    if (sz >= SZSZ_MAX) {
        MALLOC_ERROR
    } else {
        void* const ptr = malloc(sz);
        if (ptr == NULL) MALLOC_ERROR

        return ptr;
    }
}

void* mem_calloc(size_t const n, size_t const sz_elem) {
    size_t const sz = sz_elem * n;

    assert(n > 0);
    assert(sz_elem > 0);
    assert(sz / sz_elem == n);

    if (n >= SZSZ_MAX) {
        CALLOC_ERROR
    } else if (sz_elem >= SZSZ_MAX) {
        CALLOC_ERROR
    } else if (sz >= SZSZ_MAX) {
        CALLOC_ERROR
    } else {
        void* const ptr = calloc(n, sz_elem);
        if (ptr == NULL) CALLOC_ERROR

        return ptr;
    }
}

void mem_realloc(void* p_p[static const 1], size_t const new_sz) {
    assert(*p_p != NULL);
    assert(new_sz > 0);

    if (new_sz >= SZSZ_MAX) {
        REALLOC_ERROR
    } else {
        void* const p = realloc(*p_p, new_sz);
        if (p == NULL) REALLOC_ERROR

        *p_p = p;
    }
}

void mem_recalloc(
    void* p_p[static const 1],
    size_t const old_n,
    size_t const new_n,
    size_t const sz_elem
) {
    size_t const old_sz = old_n * sz_elem;
    size_t const new_sz = new_n * sz_elem;

    assert(*p_p != NULL);
    assert(old_n > 0);
    assert(old_n < new_n);
    assert(sz_elem > 0);
    assert(new_sz / new_n == sz_elem);

    if (new_n >= SZSZ_MAX) {
        RECALLOC_ERROR
    } else if (sz_elem >= SZSZ_MAX) {
        RECALLOC_ERROR
    } else if (new_sz >= SZSZ_MAX) {
        RECALLOC_ERROR
    } else {
        void* const p = calloc(new_n, sz_elem);
        if (p == NULL) RECALLOC_ERROR

        memcpy(p, *p_p, old_sz);
        *p_p = p;
    }
}
