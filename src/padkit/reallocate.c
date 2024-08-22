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

void* reallocate(
    void* ptrptr[static const 1], [[maybe_unused]] size_t const old_element_count,
    size_t const new_element_count, size_t const element_size
) {
    DEBUG_ERROR_IF(*ptrptr == NULL)
    DEBUG_ERROR_IF(old_element_count == 0)
    DEBUG_ERROR_IF(element_size == 0)
    DEBUG_ERROR_IF(new_element_count == 0)
    DEBUG_ERROR_IF(new_element_count <= old_element_count)

    {
        size_t const size = new_element_count * element_size;
        DEBUG_ERROR_IF(size < new_element_count)
        DEBUG_ERROR_IF(size < element_size)

        {
            void* const ptr = realloc(*ptrptr, size);
            if (ptr == NULL) REALLOC_ERROR

            return (*ptrptr = ptr);
        }
    }
}

void* recalloc(
    void* ptrptr[static const 1], size_t const old_element_count,
    size_t const new_element_count, size_t const element_size
) {
    DEBUG_ERROR_IF(*ptrptr == NULL)
    DEBUG_ERROR_IF(old_element_count == 0)
    DEBUG_ERROR_IF(element_size == 0)
    DEBUG_ERROR_IF(new_element_count == 0)
    DEBUG_ERROR_IF(new_element_count <= old_element_count)

    {
        size_t const memcpy_size = old_element_count * element_size;
        DEBUG_ERROR_IF(memcpy_size < old_element_count)
        DEBUG_ERROR_IF(memcpy_size < element_size)

        {
            void* const ptr = mem_calloc(new_element_count, element_size);
            memcpy(ptr, *ptrptr, memcpy_size);
            free(*ptrptr);
            return (*ptrptr = ptr);
        }
    }
}
