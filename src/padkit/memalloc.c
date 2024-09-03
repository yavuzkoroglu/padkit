#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "padkit/memalloc.h"
#include "padkit/size.h"

void* mem_alloc(size_t const size) {
    assert(size > 0);

    if (size >= SZSZ_MAX) MALLOC_ERROR

    {
        void* const ptr = malloc(size);
        if (ptr == NULL) MALLOC_ERROR

        return ptr;
    }
}

void* mem_calloc(size_t const nmemb, size_t const sz_memb) {
    size_t const sz = sz_memb * nmemb;

    assert(nmemb > 0);
    assert(sz_memb > 0);

    if (nmemb >= SZSZ_MAX) CALLOC_ERROR
    if (sz_memb >= SZSZ_MAX) CALLOC_ERROR
    if (sz >= SZSZ_MAX) CALLOC_ERROR

    assert(sz / sz_memb == nmemb);

    {
        void* const ptr = calloc(nmemb, sz_memb);
        if (ptr == NULL) CALLOC_ERROR

        return ptr;
    }
}

void mem_realloc(void* ptrptr[static const 1], size_t const new_sz) {
    assert(*ptrptr != NULL);
    assert(new_sz > 0);

    if (new_sz >= SZSZ_MAX) REALLOC_ERROR

    {
        void* const ptr = realloc(*ptrptr, new_sz);
        if (ptr == NULL) REALLOC_ERROR

        *ptrptr = ptr;
    }
}

void mem_recalloc(
    void* ptrptr[static const 1],
    size_t const old_nmemb,
    size_t const new_nmemb,
    size_t const sz_memb
) {
    size_t const old_sz = old_nmemb * sz_memb;
    size_t const new_sz = new_nmemb * sz_memb;

    assert(*ptrptr != NULL);
    assert(old_nmemb > 0);
    assert(old_nmemb < new_nmemb);
    assert(sz_memb > 0);

    if (new_nmemb >= SZSZ_MAX) RECALLOC_ERROR
    if (sz_memb >= SZSZ_MAX) RECALLOC_ERROR
    if (new_sz >= SZSZ_MAX) RECALLOC_ERROR

    assert(new_sz / new_nmemb == sz_memb);

    {
        void* const ptr = calloc(new_nmemb, sz_memb);
        if (ptr == NULL) RECALLOC_ERROR

        memcpy(ptr, *ptrptr, old_sz);
        *ptrptr = ptr;
    }
}
