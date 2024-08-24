/**
 * @file reallocate.c
 * @brief Implements the _reallocate() function defined in reallocate.h
 *
 * This implementation leaves the original pointer intact
 * when the reallocation fails.
 *
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/debug.h"
#include "padkit/memalloc.h"
#include "padkit/reallocate.h"

void* reallocate(void* ptrptr[static const 1], size_t const new_element_count, size_t const element_size) {
    DEBUG_ERROR_IF(*ptrptr == NULL)
    DEBUG_ASSERT(element_size > 0)
    DEBUG_ASSERT(element_size < SIZE_MAX >> 1)
    DEBUG_ASSERT(new_element_count > 0)
    DEBUG_ASSERT(new_element_count < SIZE_MAX >> 1)
    {
        size_t const size   = new_element_count * element_size;
        void* const ptr     = realloc(*ptrptr, size);
        DEBUG_ASSERT(size / new_element_count == size)
        if (ptr == NULL) REALLOC_ERROR
        return (*ptrptr = ptr);
    }
}

void* recalloc(
    void* ptrptr[static const 1], size_t const old_element_count,
    size_t const new_element_count, size_t const element_size
) {
    DEBUG_ERROR_IF(*ptrptr == NULL)
    DEBUG_ASSERT(old_element_count > 0)
    DEBUG_ASSERT(old_element_count < SIZE_MAX >> 1)
    DEBUG_ASSERT(element_size > 0)
    DEBUG_ASSERT(element_size < SIZE_MAX >> 1)
    DEBUG_ASSERT(new_element_count > old_element_count)
    DEBUG_ASSERT(new_element_count < SIZE_MAX >> 1)
    {
        void* const ptr             = mem_calloc(new_element_count, element_size);
        size_t const memcpy_size    = old_element_count * element_size;
        DEBUG_ASSERT(memcpy_size / old_element_count == element_size)
        memcpy(ptr, *ptrptr, memcpy_size);
        free(*ptrptr);
        return (*ptrptr = ptr);
    }
}
