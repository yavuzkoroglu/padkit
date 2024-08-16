/**
 * @file memalloc.c
 * @brief Implements mem_alloc() and mem_calloc() functions.
 * @author Yavuz Koroglu
 */
#include <stdint.h>
#include "padkit/memalloc.h"

void* mem_alloc(size_t const size) {
    #ifndef NDEBUG
        if (size == 0)          return NULL;
        if (size == SIZE_MAX)   return NULL;
    #endif

    void* const ptr = malloc(size);
    if (ptr == NULL) MALLOC_ERROR

    return ptr;
}

void* mem_calloc(size_t const nmemb, size_t const size) {
    #ifndef NDEBUG
        if (nmemb == 0)         return NULL;
        if (nmemb == SIZE_MAX)  return NULL;
        if (size == 0)          return NULL;
        if (size == SIZE_MAX)   return NULL;
    #endif

    void* const ptr = calloc(nmemb, size);
    if (ptr == NULL) CALLOC_ERROR

    return ptr;
}
