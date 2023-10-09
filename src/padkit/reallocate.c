/**
 * @file reallocate.c
 * @brief Implements the _reallocate() function defined in reallocate.h
 *
 * This implementation leaves the original pointer intact
 * when the reallocation fails.
 *
 * @author Yavuz Koroglu
 */
#include <stdlib.h>
#include <string.h>
#include "padkit/reallocate.h"

void* reallocate(
    void** ptrptr, size_t const old_element_count,
    size_t const new_element_count, size_t const element_size
) {
    #ifndef NDEBUG
        if (ptrptr == NULL)                         return NULL;
        if (*ptrptr == NULL)                        return NULL;
        if (old_element_count == 0)                 return NULL;
        if (element_size == 0)                      return NULL;
        if (new_element_count == 0)                 return NULL;
        if (new_element_count <= old_element_count) return NULL;

        size_t const size = new_element_count * element_size;
        if (size < new_element_count || size < element_size) return NULL;

        void* const ptr = realloc(*ptrptr, new_element_count * element_size);
        if (ptr == NULL) return NULL;
        *ptrptr = ptr;
    #else
        *ptrptr = realloc(*ptrptr, new_element_count * element_size);
    #endif
    return *ptrptr;
}

void* recalloc(
    void** ptrptr, size_t const old_element_count,
    size_t const new_element_count, size_t const element_size
) {
    #ifndef NDEBUG
        if (ptrptr == NULL)                         return NULL;
        if (*ptrptr == NULL)                        return NULL;
        if (old_element_count == 0)                 return NULL;
        if (element_size == 0)                      return NULL;
        if (new_element_count == 0)                 return NULL;
        if (new_element_count <= old_element_count) return NULL;
    #endif

    size_t const memcpy_size = old_element_count * element_size;
    #ifndef NDEBUG
        if (memcpy_size < old_element_count || memcpy_size < element_size)
            return NULL;
    #endif

    void* const ptr = calloc(new_element_count, element_size);
    #ifndef NDEBUG
        if (ptr == NULL) return NULL;
    #endif

    memcpy(ptr, *ptrptr, memcpy_size);
    free(*ptrptr);
    *ptrptr = ptr;
    return ptr;
}
