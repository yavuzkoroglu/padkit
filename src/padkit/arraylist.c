#include <assert.h>
#include <string.h>
#include "padkit/arraylist.h"
#include "padkit/invalid.h"
#include "padkit/memalloc.h"
#include "padkit/size.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

void* add_alist(ArrayList list[static const 1], uint32_t const n, void const* const restrict ptr) {
    uint32_t new_cap = list->cap;

    assert(isValid_alist(list));
    assert(n > 0);
    assert(n < SZ32_MAX);

    while (new_cap - list->size < n) {
        new_cap <<= 1;
        if (new_cap >= SZ32_MAX)
            REALLOC_ERROR
    }

    if (new_cap > list->cap) {
        size_t const sz_new = list->sz_element * (size_t)new_cap;
        #ifndef NDEBUG
            size_t const sz_array   = list->sz_element * (size_t)list->cap;
            size_t const sz_ptr     = list->sz_element * (size_t)n;
        #endif
        assert(sz_new < SZSZ_MAX);
        assert(sz_ptr < SZSZ_MAX);
        assert(sz_new / list->sz_element == (size_t)new_cap);
        assert(sz_ptr / list->sz_element == (size_t)n);
        assert(!overlaps_ptr(list->array, ptr, sz_array, sz_ptr));

        /* Invalidates ptr if ptr and list->array overlap. */
        mem_realloc((void**)&(list->array), sz_new);
        list->cap = new_cap;
    }

    list->size += n;

    if (ptr == NULL)
        return get_alist(list, list->size - n);
    else
        return set_alist(list, list->size - n, n, ptr);
}

void* addIndeterminate_alist(ArrayList list[static const 1], uint32_t const n) {
    assert(isValid_alist(list));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return add_alist(list, n, NULL);
}

void* addZeros_alist(ArrayList list[static const 1], uint32_t const n) {
    assert(isValid_alist(list));
    assert(n > 0);
    assert(n < SZ32_MAX);

    addIndeterminate_alist(list, n);
    return setZeros_alist(list, list->size - n, n);
}

uint32_t bsearch_alist(
    void* key[static const 1],
    ArrayList const list[static const 1],
    void const* const ptr,
    int (*compar)(void const*, void const*)
) {
    assert(isValid_alist(list));
    assert(ptr != NULL);
    assert(compar != NULL);
    assert(isSorted_alist(list, compar));

    {
        char* const candidate = bsearch(ptr, list->array, list->size, list->sz_element, compar);
        if (candidate == NULL) {
            *key = NULL;
            return INVALID_UINT32;
        }

        assert(candidate >= list->array);
        {
            ptrdiff_t const offset  = candidate - list->array;
            size_t const id         = (size_t)offset / list->sz_element;
            assert(offset >= 0);
            assert(offset < SZPTRDIFF_MAX);
            assert((size_t)offset % list->sz_element == 0);
            assert(id < SZ32_MAX);
            assert((uint32_t)id < list->size);

            *key = candidate;
            return (uint32_t)id;
        }
    }
}

void concat_alist(ArrayList head[static const restrict 1], ArrayList const tail[static const restrict 1]) {
    #ifndef NDEBUG
        size_t const sz_head = head->sz_element * (size_t)head->size;
        size_t const sz_tail = tail->sz_element * (size_t)tail->size;
    #endif
    assert(isValid_alist(head));
    assert(isValid_alist(tail));
    assert(sz_head < SZSZ_MAX);
    assert(sz_tail < SZSZ_MAX);
    assert(sz_head / head->sz_element == (size_t)head->size);
    assert(sz_tail / tail->sz_element == (size_t)tail->size);

    if (tail->size == 0) return;

    assert(!overlaps_ptr(head->array, tail->array, sz_head, sz_tail));

    add_alist(head, tail->size, tail->array);
}

void constructEmpty_alist(
    ArrayList list[static const 1],
    size_t const sz_element,
    uint32_t const initial_cap
) {
    size_t const sz = sz_element * (size_t)initial_cap;

    assert(sz_element > 0);
    assert(sz_element < SZSZ_MAX);
    assert(initial_cap > 0);
    assert(initial_cap < SZ32_MAX);
    assert(sz / sz_element == (size_t)initial_cap);

    list->sz_element    = sz_element;
    list->cap           = initial_cap;
    list->size          = 0;
    list->array         = mem_alloc(sz);
}

void flush_alist(ArrayList list[static const 1]) {
    assert(isValid_alist(list));
    list->size = 0;
}

void free_alist(ArrayList list[static const 1]) {
    assert(isValid_alist(list));
    free(list->array);
    list[0] = NOT_AN_ALIST;
}

void* get_alist(ArrayList const list[static const 1], uint32_t const id) {
    size_t const offset = list->sz_element * (size_t)id;

    assert(isValid_alist(list));
    assert(id < list->size);
    assert(offset < SZSZ_MAX);
    assert(offset / list->sz_element == (size_t)id);

    return list->array + offset;
}

bool isSorted_alist(ArrayList const list[static const 1], int (*compar)(void const*, void const*)) {
    assert(isValid_alist(list));
    assert(compar != NULL);

    if (list->size == 0) {
        return 1;
    } else {
        void const* p[2] = { NULL, get_alist(list, 0) };
        for (uint32_t i = 1; i < list->size; i++) {
            p[0] = p[1];
            p[1] = get_alist(list, i);

            if (compar(p[0], p[1]) > 0)
                return 0;
        }

        return 1;
    }
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

uint32_t lsearch_alist(void* key[static const 1], ArrayList const list[static const 1], void const* const ptr) {
    #ifndef NDEBUG
        size_t const sz = list->sz_element * (size_t)list->size;
    #endif
    assert(isValid_alist(list));
    assert(sz < SZSZ_MAX);
    assert(sz / list->sz_element == (size_t)list->size);
    assert(ptr != NULL);

    for (uint32_t i = 0; i < list->size; i++) {
        key[0] = get_alist(list, i);
        if (memcmp(key[0], ptr, list->sz_element) == 0)
            return i;
    }

    key[0] = NULL;
    return INVALID_UINT32;
}

void qsort_alist(ArrayList const list[static const 1], int (*compar)(void const*, void const*)) {
    assert(isValid_alist(list));
    assert(compar != NULL);

    qsort(list->array, list->size, list->sz_element, compar);
}

void* removeLast_alist(ArrayList list[static const 1], uint32_t const n) {
    assert(isValid_alist(list));
    assert(n > 0);
    assert(n <= list->size);

    {
        void* const ptr = get_alist(list, list->size - n);
        list->size -= n;
        return ptr;
    }
}

void reverse_alist(ArrayList list[static const 1]) {
    assert(isValid_alist(list));

    if (list->size > 1) {
        char* const buffer  = mem_alloc(list->sz_element);
        char* bottom        = get_alist(list, 0);
        char* top           = get_alist(list, list->size - 1);

        /* (bottom < top) is NOT UB because
         * both belong to list->array. */
        while (bottom < top) {
            memcpy(buffer, bottom, list->sz_element);
            memcpy(bottom, top, list->sz_element);
            memcpy(top, buffer, list->sz_element);

            bottom += list->sz_element;
            top -= list->sz_element;
        }

        free(buffer);
    }
}

void* set_alist(
    ArrayList list[static const 1],
    uint32_t const startId,
    uint32_t const n,
    void const* const restrict ptr
) {
    assert(isValid_alist(list));
    assert(startId < list->size);
    assert(n > 0);
    assert(n <= list->size - startId);

    {
        void* const dest    = get_alist(list, startId);
        size_t const sz     = list->sz_element * (size_t)n;

        assert(sz < SZSZ_MAX);
        assert(sz / list->sz_element == (size_t)n);

        if (ptr == NULL) {
            memset(dest, 0, sz);
        } else {
            #ifndef NDEBUG
                size_t const sz_array = list->sz_element * (size_t)(list->size - startId);
            #endif
            assert(sz_array < SZSZ_MAX);
            assert(sz_array / list->sz_element == (size_t)(list->size - startId));
            assert(!overlaps_ptr(dest, ptr, sz_array, sz));

            /* UB if ptr and list->array + startId overlap. */
            memcpy(dest, ptr, sz);
        }

        return dest;
    }
}

void* setZeros_alist(ArrayList list[static const 1], uint32_t const startId, uint32_t const n) {
    assert(isValid_alist(list));
    assert(startId < list->size);
    assert(n > 0);
    assert(n <= list->size - startId);

    return set_alist(list, startId, n, NULL);
}
