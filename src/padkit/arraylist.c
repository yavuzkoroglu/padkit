#include <string.h>
#include "padkit/arraylist.h"
#include "padkit/debug.h"
#include "padkit/memalloc.h"
#include "padkit/size.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

void add_alist(ArrayList list[static const 1], uint32_t const n, void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_alist(list))
    DEBUG_ASSERT(n > 0)
    DEBUG_ASSERT(n < SZ32_MAX)

    {
        uint32_t new_cap = list->cap;
        while (new_cap - list->size < n) {
            new_cap <<= 1;
            if (new_cap >= SZ32_MAX)
                REALLOC_ERROR
        }

        if (new_cap > list->cap) {
            DEBUG_EXECUTE(size_t const sz_array = list->sz_element * (size_t)list->cap)
            DEBUG_EXECUTE(size_t const sz_ptr   = list->sz_element * (size_t)n)
            DEBUG_ASSERT(sz_array < SZSZ_MAX)
            DEBUG_ASSERT(sz_ptr < SZSZ_MAX)
            DEBUG_ASSERT(sz_array / list->sz_element == (size_t)list->cap)
            DEBUG_ASSERT(sz_array / sz_ptr == (size_t)n)
            DEBUG_ERROR_IF(overlaps_ptr(list->array, ptr, sz_array, sz_ptr))
            realloc_alist(list, new_cap); /* UB if ptr overlaps with list->array. */
        }
    }

    list->size += n;

    set_alist(list, list->size - n, n, ptr);
}

void addZeros_alist(ArrayList list[static const 1], uint32_t const n) {
    DEBUG_ASSERT(isValid_alist(list))
    DEBUG_ASSERT(n > 0)
    DEBUG_ASSERT(n < SZ32_MAX)

    add_alist(list, n, NULL);
}

void constructEmpty_alist(
    ArrayList list[static const 1],
    size_t const sz_element,
    uint32_t const initial_cap
) {
    size_t const sz = sz_element * (size_t)initial_cap;

    DEBUG_ASSERT(sz_element > 0)
    DEBUG_ASSERT(sz_element < SZSZ_MAX)
    DEBUG_ASSERT(initial_cap > 0)
    DEBUG_ASSERT(initial_cap < SZ32_MAX)
    DEBUG_ASSERT(sz / sz_element == (size_t)initial_cap)

    list->sz_element    = sz_element;
    list->cap           = initial_cap;
    list->size          = 0;
    list->array         = mem_alloc(sz);
}

void flush_alist(ArrayList list[static const 1]) {
    DEBUG_ASSERT(isValid_alist(list))
    list->size = 0;
}

void free_alist(ArrayList list[static const 1]) {
    DEBUG_ASSERT(isValid_alist(list))
    free(list->array);
    list[0] = NOT_AN_ALIST;
}

void* get_alist(ArrayList const list[static const 1], uint32_t const id) {
    size_t const offset = list->sz_element * (size_t)id;

    DEBUG_ASSERT(isValid_alist(list))
    DEBUG_ASSERT(id < list->size)
    DEBUG_ASSERT(offset < SZSZ_MAX)
    DEBUG_ASSERT(offset / list->sz_element == (size_t)id)

    return list->array + offset;
}

bool isValid_alist(ArrayList const list[static const 1]) {
    if (list->sz_element == 0)          return 0;
    if (list->sz_element >= SZSZ_MAX)   return 0;
    if (list->cap == 0)                 return 0;
    if (list->cap >= SZ32_MAX)          return 0;
    if (list->size > list->cap)         return 0;
    if (list->array == NULL)            return 0;

    return 1;
}

void realloc_alist(ArrayList list[static const 1], uint32_t const new_cap) {
    size_t const new_sz = list->sz_element * (size_t)new_cap;

    DEBUG_ASSERT(isValid_alist(list))
    DEBUG_ASSERT(new_cap > list->cap)
    DEBUG_ASSERT(new_cap < SZ32_MAX)
    DEBUG_ASSERT(new_sz < SZSZ_MAX)
    DEBUG_ASSERT(new_sz / list->sz_element == (size_t)new_cap)

    mem_realloc((void**)&(list->array), new_sz);
}

void set_alist(
    ArrayList list[static const 1],
    uint32_t const startId,
    uint32_t const n,
    void const* const restrict ptr
) {
    size_t const sz = list->sz_element * (size_t)n;

    DEBUG_ASSERT(isValid_alist(list))
    DEBUG_ASSERT(startId < list->size)
    DEBUG_ASSERT(n > 0)
    DEBUG_ASSERT(n <= list->size - startId)
    DEBUG_ASSERT(sz < SZSZ_MAX)
    DEBUG_ASSERT(sz / list->sz_element == (size_t)n)

    if (ptr == NULL) {
        memset(list->array + startId, 0, sz);
    } else {
        DEBUG_EXECUTE(size_t const sz_array = list->sz_element * (size_t)(list->size - startId))
        DEBUG_ASSERT(sz_array < SZSZ_MAX)
        DEBUG_ERROR_IF(overlaps_ptr(list->array + startId, ptr, sz_array, sz))
        memcpy(list->array + startId, ptr, sz); /* UB if ptr and list->array + startId overlap. */
    }
}

void setZeros_alist(ArrayList list[static const 1], uint32_t const startId, uint32_t const n) {
    DEBUG_ASSERT(isValid_alist(list))
    DEBUG_ASSERT(startId < list->size)
    DEBUG_ASSERT(n > 0)
    DEBUG_ASSERT(n <= list->size - startId)

    set_alist(list, startId, n, NULL);
}
