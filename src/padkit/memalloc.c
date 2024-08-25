/**
 * @file memalloc.c
 * @brief Implements mem_alloc() and mem_calloc() functions.
 * @author Yavuz Koroglu
 */
#include <stdint.h>
#include "padkit/debug.h"
#include "padkit/memalloc.h"

void* mem_alloc(size_t const size) {
    DEBUG_ASSERT(size > 0)
    DEBUG_ASSERT(size < RSIZE_MAX)
    {
        void* const ptr = malloc(size);
        if (ptr == nullptr) MALLOC_ERROR

        return ptr;
    }
}

void* mem_calloc(size_t const nmemb, size_t const size) {
    DEBUG_ASSERT(nmemb > 0)
    DEBUG_ASSERT(nmemb < RSIZE_MAX)
    DEBUG_ASSERT(size > 0)
    DEBUG_ASSERT(size < RSIZE_MAX)
    DEBUG_ASSERT((nmemb * size) / nmemb == size)
    {
        void* const ptr = calloc(nmemb, size);
        if (ptr == nullptr) CALLOC_ERROR

        return ptr;
    }
}
