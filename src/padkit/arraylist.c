#include <assert.h>
#include <string.h>
#include "padkit/arraylist.h"
#include "padkit/invalid.h"
#include "padkit/memalloc.h"
#include "padkit/size.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

void* addDuplicate_alist(
    ArrayList list[static const 1],
    uint32_t const id
) {
    assert(isValid_alist(list));
    assert(list->len > id);

    return addDuplicates_alist(list, id, 1);
}

void* addDuplicates_alist(
    ArrayList list [static const 1],
    uint32_t const id,
    uint32_t const n
) {
    assert(isValid_alist(list));
    assert(list->len > id);
    assert(n > 0);
    assert(n < SZ32_MAX);

    addIndeterminates_alist(list, n);
    assert(list->len >= n);

    return setDuplicates_alist(list, id, list->len - n, n);
}

void* addElement_alist(
    ArrayList list[static const 1],
    void const* const p
) {
    assert(isValid_alist(list));
    return addElements_alist(list, p, 1);
}

void* addElements_alist(
    ArrayList list[static const 1],
    void const* const p,
    uint32_t const n
) {
    uint32_t new_cap = list->cap;

    assert(isValid_alist(list));
    assert(n > 0);
    assert(n < SZ32_MAX);

    while (new_cap - list->len < n) {
        new_cap <<= 1;
        if (new_cap >= SZ32_MAX)
            REALLOC_ERROR
    }

    if (new_cap > list->cap) {
        size_t const sz_new = list->sz_elem * (size_t)new_cap;
        #ifndef NDEBUG
            size_t const sz_arr = list->sz_elem * (size_t)list->cap;
            size_t const sz_p   = list->sz_elem * (size_t)n;
        #endif
        assert(sz_new < SZSZ_MAX);
        assert(sz_p < SZSZ_MAX);
        assert(sz_new / list->sz_elem == (size_t)new_cap);
        assert(sz_p / list->sz_elem == (size_t)n);
        assert(!overlaps_ptr(list->arr, p, sz_arr, sz_p));

        /* Invalidates p if p and list->arr overlap. */
        mem_realloc((void**)&(list->arr), sz_new);
        list->cap = new_cap;
    }

    list->len += n;
    assert(list->len >= n);

    if (p == NULL)
        return get_alist(list, list->len - n);
    else
        return setElements_alist(list, list->len - n, p, n);
}

void* addIndeterminate_alist(ArrayList list[static const 1]) {
    assert(isValid_alist(list));
    return addIndeterminates_alist(list, 1);
}

void* addIndeterminates_alist(ArrayList list[static const 1], uint32_t const n) {
    assert(isValid_alist(list));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return addElements_alist(list, NULL, n);
}

void* addZero_alist(ArrayList list[static const 1]) {
    assert(isValid_alist(list));
    return addZeros_alist(list, 1);
}

void* addZeros_alist(ArrayList list[static const 1], uint32_t const n) {
    assert(isValid_alist(list));
    assert(n > 0);
    assert(n < SZ32_MAX);

    addIndeterminates_alist(list, n);
    assert(list->len >= n);

    return setZeros_alist(list, list->len - n, n);
}

uint32_t bsearch_alist(
    void* key[static const 1],
    ArrayList const list[static const 1],
    void const* const p,
    int (*cmp)(void const*, void const*)
) {
    assert(isValid_alist(list));
    assert(p != NULL);
    assert(cmp != NULL);
    assert(isSorted_alist(list, cmp));

    {
        char* const candidate = bsearch(p, list->arr, list->len, list->sz_elem, cmp);
        if (candidate == NULL) {
            key[0] = NULL;
            return INVALID_UINT32;
        }

        assert(candidate >= list->arr);
        {
            ptrdiff_t const offset  = candidate - list->arr;
            size_t const id         = (size_t)offset / list->sz_elem;
            assert(offset >= 0);
            assert(offset < SZPTRDIFF_MAX);
            assert((size_t)offset % list->sz_elem == 0);
            assert(id < SZ32_MAX);
            assert((uint32_t)id < list->len);

            key[0] = candidate;
            return (uint32_t)id;
        }
    }
}

void concat_alist(
    ArrayList head[static const 1],
    ArrayList const tail[static const 1]
) {
    #ifndef NDEBUG
        size_t const sz_head = head->sz_elem * (size_t)head->len;
        size_t const sz_tail = tail->sz_elem * (size_t)tail->len;
    #endif
    assert(isValid_alist(head));
    assert(isValid_alist(tail));
    assert(sz_head < SZSZ_MAX);
    assert(sz_tail < SZSZ_MAX);
    assert(sz_head / head->sz_elem == (size_t)head->len);
    assert(sz_tail / tail->sz_elem == (size_t)tail->len);

    if (tail->len == 0) return;

    #ifndef NDEBUG
        if (head->cap - head->len < tail->len)
            assert(!overlaps_ptr(head->arr, tail->arr, sz_head, sz_tail));
    #endif

    /* Invalidates head->arr if
       head->arr must be relocated
       and head->arr overlaps with tail->arr. */
    addElements_alist(head, tail->arr, tail->len);
}

void construct_alist(void* const p_list, ...) {
    va_list args;
    assert(p_list != NULL);
    va_start(args, p_list);
    vconstruct_alist(p_list, args);
}

void constructEmpty_alist(
    ArrayList list[static const 1],
    size_t const sz_elem,
    uint32_t const init_cap
) {
    size_t const sz = sz_elem * (size_t)init_cap;

    assert(sz_elem > 0);
    assert(sz_elem < SZSZ_MAX);
    assert(init_cap > 0);
    assert(init_cap < SZ32_MAX);
    assert(sz / sz_elem == (size_t)init_cap);

    list->sz_elem   = sz_elem;
    list->cap       = init_cap;
    list->len       = 0;
    list->arr       = mem_alloc(sz);
}

void deleteElement_alist(
    ArrayList list[static const 1],
    uint32_t const id
) {
    assert(isValid_alist(list));
    assert(list->len > id);

    deleteElements_alist(list, id, 1);
}

void deleteElements_alist(
    ArrayList list[static const 1],
    uint32_t const id,
    uint32_t const n
) {
    assert(isValid_alist(list));
    assert(list->len > id);
    assert(list->len - id >= n);
    assert(n > 0);

    if (id + n == list->len) {
        removeLast_alist(list, n);
    } else {
        uint32_t const len  = (list->len - id) - n;
        size_t const sz     = list->sz_elem * (size_t)(len);
        void* const dest    = get_alist(list, id);
        void* const src     = get_alist(list, id + n);
        assert(sz < SZSZ_MAX);
        assert(sz / list->sz_elem == (size_t)(len));

        memmove(dest, src, sz);
        list->len -= n;
    }
}

void destruct_alist(void* const p_list) {
    ArrayList* const list = (ArrayList*)p_list;
    assert(isValid_alist(list));
    free(list->arr);
    list[0] = NOT_AN_ALIST;
}

void flush_alist(ArrayList list[static const 1]) {
    assert(isValid_alist(list));
    list->len = 0;
}

void* get_alist(
    ArrayList const list[static const 1],
    uint32_t const id
) {
    size_t const offset = list->sz_elem * (size_t)id;

    assert(isValid_alist(list));
    assert(list->len > id);
    assert(offset < SZSZ_MAX);
    assert(offset / list->sz_elem == (size_t)id);

    return list->arr + offset;
}

void* getFirst_alist(ArrayList const list[static const 1]) {
    assert(isValid_alist(list));
    assert(list->len > 0);

    return get_alist(list, 0);
}

void* getLast_alist(ArrayList const list[static const 1]) {
    assert(isValid_alist(list));
    assert(list->len > 0);

    return get_alist(list, list->len - 1);
}

bool isAllocated_alist(void const* const p_list) {
    ArrayList const* const list = (ArrayList const*)p_list;

    if (list == NULL)       return 0;
    if (list->arr == NULL)  return 0;

    return 1;
}

bool isSorted_alist(
    ArrayList const list[static const 1],
    int (*cmp)(void const*, void const*)
) {
    assert(isValid_alist(list));
    assert(cmp != NULL);

    if (list->len <= 1) {
        return 1;
    } else {
        void const* p[2] = { NULL, get_alist(list, 0) };
        for (uint32_t i = 1; i < list->len; i++) {
            p[0] = p[1];
            p[1] = get_alist(list, i);

            if (cmp(p[0], p[1]) > 0)
                return 0;
        }

        return 1;
    }
}

bool isValid_alist(void const* const p_list) {
    ArrayList const* const list = (ArrayList const*)p_list;

    if (!isAllocated_alist(list))   return 0;
    if (list->sz_elem == 0)         return 0;
    if (list->sz_elem >= SZSZ_MAX)  return 0;
    if (list->cap == 0)             return 0;
    if (list->cap >= SZ32_MAX)      return 0;
    if (list->len > list->cap)      return 0;

    return 1;
}

uint32_t lsearch_alist(
    void* key[static const 1],
    ArrayList const list[static const 1],
    void const* const p
) {
    #ifndef NDEBUG
        size_t const sz = list->sz_elem * (size_t)list->len;
    #endif
    assert(isValid_alist(list));
    assert(sz < SZSZ_MAX);
    assert(sz / list->sz_elem == (size_t)list->len);
    assert(p != NULL);

    for (uint32_t i = 0; i < list->len; i++) {
        key[0] = get_alist(list, i);
        if (memcmp(key[0], p, list->sz_elem) == 0)
            return i;
    }

    key[0] = NULL;
    return INVALID_UINT32;
}

void qsort_alist(
    ArrayList const list[static const 1],
    int (*cmp)(void const*, void const*)
) {
    assert(isValid_alist(list));
    assert(cmp != NULL);

    qsort(list->arr, list->len, list->sz_elem, cmp);
}

void* removeLast_alist(ArrayList list[static const 1], uint32_t const n) {
    assert(isValid_alist(list));
    assert(n > 0);
    assert(list->len >= n);
    {
        void* const p = get_alist(list, list->len - n);
        list->len -= n;
        return p;
    }
}

void reverse_alist(ArrayList list[static const 1]) {
    assert(isValid_alist(list));

    if (list->len > 1) {
        char* const buf = mem_alloc(list->sz_elem);
        char* bot       = get_alist(list, 0);
        char* top       = get_alist(list, list->len - 1);

        /* (bot < top) is NOT UB because
         * both belong to list->arr. */
        while (bot < top) {
            memcpy(buf, bot, list->sz_elem);
            memcpy(bot, top, list->sz_elem);
            memcpy(top, buf, list->sz_elem);

            bot += list->sz_elem;
            top -= list->sz_elem;
        }

        free(buf);
    }
}

void* setDuplicate_alist(
    ArrayList list[static const 1],
    uint32_t const orig_id,
    uint32_t const dup_id
) {
    assert(isValid_alist(list));
    assert(list->len > orig_id);
    assert(list->len > dup_id);

    return setDuplicates_alist(list, orig_id, dup_id, 1);
}

void* setDuplicates_alist(
    ArrayList list[static const 1],
    uint32_t const orig_id,
    uint32_t const dup_id,
    uint32_t const n
) {
    assert(isValid_alist(list));
    assert(list->len > orig_id);
    assert(list->len > dup_id);
    assert(n <= list->len - orig_id);
    assert(n <= list->len - dup_id);
    assert(n > 0);

    if (orig_id == dup_id) {
        return get_alist(list, dup_id);
    } else {
        void* const p_orig  = get_alist(list, orig_id);
        void* const p_dup   = get_alist(list, dup_id);
        size_t const sz     = list->sz_elem * (size_t)n;
        assert(sz < SZSZ_MAX);
        assert(sz / list->sz_elem == (size_t)n);
        return memmove(p_dup, p_orig, sz);
    }
}

void* setElement_alist(
    ArrayList list[static const 1],
    uint32_t const id,
    void const* const p
) {
    assert(isValid_alist(list));
    assert(list->len > id);

    return setElements_alist(list, id, p, 1);
}

void* setElements_alist(
    ArrayList list[static const 1],
    uint32_t const id,
    void const* const p,
    uint32_t const n
) {
    assert(isValid_alist(list));
    assert(list->len > id);
    assert(n > 0);
    assert(n <= list->len - id);
    {
        void* const dest    = get_alist(list, id);
        size_t const sz     = list->sz_elem * (size_t)n;

        assert(sz < SZSZ_MAX);
        assert(sz / list->sz_elem == (size_t)n);

        if (p == NULL) {
            memset(dest, 0, sz);
        } else {
            #ifndef NDEBUG
                size_t const sz_arr = list->sz_elem * (size_t)(list->len - id);
            #endif
            assert(sz_arr < SZSZ_MAX);
            assert(sz_arr / list->sz_elem == (size_t)(list->len - id));
            assert(!overlaps_ptr(dest, p, sz_arr, sz));

            /* UB if dest and p overlap. */
            memcpy(dest, p, sz);
        }

        return dest;
    }
}

void* setZero_alist(
    ArrayList list[static const 1],
    uint32_t const id
) {
    assert(isValid_alist(list));
    assert(list->len > id);

    return setZeros_alist(list, id, 1);
}

void* setZeros_alist(
    ArrayList list[static const 1],
    uint32_t const id,
    uint32_t const n
) {
    assert(isValid_alist(list));
    assert(list->len > id);
    assert(n <= list->len - id);
    assert(n > 0);

    return setElements_alist(list, id, NULL, n);
}

void vconstruct_alist(void* const p_list, va_list args) {
    ArrayList* const list   = (ArrayList*)p_list;
    size_t const sz_elem    = va_arg(args, size_t);
    uint32_t const init_cap = va_arg(args, uint32_t);

    assert(list != NULL);
    assert(sz_elem > 0);
    assert(sz_elem < SZSZ_MAX);
    assert(init_cap > 0);
    assert(init_cap < SZ32_MAX);

    constructEmpty_alist(list, sz_elem, init_cap);
}

