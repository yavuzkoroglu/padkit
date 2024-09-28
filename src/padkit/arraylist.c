#include <assert.h>
#include <string.h>
#include "padkit/arraylist.h"
#include "padkit/invalid.h"
#include "padkit/memalloc.h"
#include "padkit/size.h"
#include "padkit/unused.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

void* addDupN_alist(
    ArrayList list [static const 1],
    uint32_t const id,
    uint32_t const n
) {
    uint32_t const len = list->len;

    assert(isValid_alist(list));
    assert(len > id);
    assert(n > 0);
    assert(n < SZ32_MAX - len);

    addIndeterminateN_alist(list, n);
    return setDupN_alist(list, len, id, n);
}

void* addN_alist(
    ArrayList list[static const 1],
    void const* const p,
    uint32_t const n
) {
    uint32_t const old_len = list->len;
    uint32_t const new_len = old_len + n;

    assert(isValid_alist(list));
    assert(n > 0);
    assert(n < SZ32_MAX - old_len);
    {
        uint32_t new_cap = list->cap;
        while (new_cap < new_len) {
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
    }

    list->len = new_len;
    if (p == NULL)
        return getN_alist(list, old_len, n);
    else
        return setN_alist(list, old_len, p, n);
}

void* addZerosN_alist(ArrayList list[static const 1], uint32_t const n) {
    uint32_t const len = list->len;

    assert(isValid_alist(list));
    assert(n > 0);
    assert(n < SZ32_MAX - len);

    addIndeterminateN_alist(list, n);
    return setZerosN_alist(list, len, n);
}

uint32_t bsearch_alist(
    void* p_key[static const 1],
    ArrayList const list[static const 1],
    void const* const p,
    int (*cmp)(void const*, void const*)
) {
    assert(isValid_alist(list));
    assert(p != NULL);
    assert(cmp != NULL);
    assert(isSorted_alist(list, cmp));

    p_key[0] = bsearch(p, list->arr, list->len, list->sz_elem, cmp);
    if (p_key[0] == NULL) {
        return INVALID_UINT32;
    } else {
        ptrdiff_t const offset  = (char*)p_key[0] - list->arr;
        size_t const id         = (size_t)offset / list->sz_elem;
        assert(offset >= 0);
        assert(offset < SZPTRDIFF_MAX);
        assert((size_t)offset % list->sz_elem == 0);
        assert(id < SZ32_MAX);
        assert((uint32_t)id < list->len);

        return (uint32_t)id;
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
    addN_alist(head, tail->arr, tail->len);
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

void* getLastN_alist(
    ArrayList const list[static const 1],
    uint32_t const n
) {
    size_t const offset = list->sz_elem * (size_t)(list->len - n);

    assert(isValid_alist(list));
    assert(list->len >= n);
    assert(n > 0);
    assert(offset < SZSZ_MAX);
    assert(offset / list->sz_elem == (size_t)(list->len - n));

    return list->arr + offset;
}

void* getN_alist(
    ArrayList const list[static const 1],
    uint32_t const id,
    uint32_t const n
) {
    size_t const offset = list->sz_elem * (size_t)id;
    MAYBE_UNUSED(n)

    assert(isValid_alist(list));
    assert(list->len > id);
    assert(list->len - id >= n);
    assert(n > 0);
    assert(offset < SZSZ_MAX);
    assert(offset / list->sz_elem == (size_t)id);

    return list->arr + offset;
}

void* insertDupN_alist(
    ArrayList list[static const 1],
    uint32_t const dup_id,
    uint32_t const orig_id,
    uint32_t const n
) {
    uint32_t const len = list->len;

    assert(isValid_alist(list));
    assert(len > dup_id);
    assert(len > orig_id);
    assert(dup_id != orig_id);
    assert(len - orig_id >= n);
    assert(n > 0);

    addIndeterminateN_alist(list, n);
    addDupN_alist(list, orig_id, n);
    setDupN_alist(list, dup_id + n, dup_id, len - dup_id);
    {
        void* const p = setDupN_alist(list, dup_id, len + n, n);
        removeLastN_alist(list, n);
        return p;
    }
}

void* insertN_alist(
    ArrayList list[static const 1],
    uint32_t const id,
    void const* const p,
    uint32_t const n
) {
    uint32_t const len = list->len;

    assert(isValid_alist(list));
    assert(len > id);
    assert(n < SZ32_MAX - len);
    assert(n > 0);

    #ifndef NDEBUG
        if (len + n > list->cap) {
            size_t const sz_arr = list->sz_elem * (size_t)list->len;
            assert(sz_arr < SZSZ_MAX);
            assert(sz_arr / list->sz_elem == (size_t)list->len);
            assert(!overlaps_ptr(list->arr, p, sz_arr, list->sz_elem));
        }
    #endif

    /* Invalidates p if list->arr has to be reallocated and list->arr overlaps with p. */
    addIndeterminateN_alist(list, n);

    setDupN_alist(list, id + n, id, len - id);
    return setN_alist(list, id, p, n);
}

void* insertZerosN_alist(
    ArrayList list[static const 1],
    uint32_t const id,
    uint32_t const n
) {
    uint32_t const len = list->len;

    assert(isValid_alist(list));
    assert(len > id);
    assert(n < SZ32_MAX - len);
    assert(n > 0);

    addIndeterminateN_alist(list, n);
    setDupN_alist(list, id + n, id, len - id);
    return setZerosN_alist(list, id, n);
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
        char const* p[] = { NULL, getFirst_alist(list) };
        for (uint32_t i = 1; i < list->len; i++) {
            p[0] = p[1];
            p[1] += list->sz_elem;

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
    void* p_key[static const 1],
    ArrayList const list[static const 1],
    void const* const p
) {
    assert(isValid_alist(list));
    assert(p != NULL);

    p_key[0] = getFirst_alist(list);
    for (uint32_t i = 0; i < list->len; i++) {
        if (memcmp(p_key[0], p, list->sz_elem) == 0)
            return i;

        p_key[0] = (char*)p_key[0] + list->sz_elem;
    }

    p_key[0] = NULL;
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

void* removeLastN_alist(
    ArrayList list[static const 1],
    uint32_t const n
) {
    assert(isValid_alist(list));
    assert(n > 0);
    assert(list->len >= n);
    {
        void* const p = getN_alist(list, list->len - n, n);
        list->len -= n;
        return p;
    }
}

void* removeN_alist(
    ArrayList list[static const 1],
    uint32_t const id,
    uint32_t const n
) {
    uint32_t const old_len  = list->len;
    uint32_t const new_len  = old_len - n;
    uint32_t const shft_len = new_len - id;

    assert(isValid_alist(list));
    assert(old_len > id);
    assert(old_len - id >= n);
    assert(n > 0);

    if (shft_len == 0) {
        /* Do Nothing */
    } else if (n <= shft_len) {
        addDupN_alist(list, id, n);
        setDupN_alist(list, id, id + n, shft_len + n);
        removeLastN_alist(list, n);
    } else {
        addIndeterminateN_alist(list, shft_len);
        setDupN_alist(list, new_len, id, old_len - id);
        setDupN_alist(list, id, old_len, shft_len);
        removeLastN_alist(list, shft_len);
    }

    return removeLastN_alist(list, n);
}

void reverse_alist(ArrayList list[static const 1]) {
    assert(isValid_alist(list));

    if (list->len <= 1) return;

    for (
        uint32_t i = 0, j = list->len - 1;
        i < j;
        i++, j--
    ) swap_alist(list, i, j);
}

void rotateDownN_alist(
    ArrayList list[static const 1],
    uint32_t n
) {
    uint32_t const len = list->len;

    assert(isValid_alist(list));

    if ((n %= len) == 0) {
        /* Do nothing */
    } else if (n >= len >> 1) {
        rotateUpN_alist(list, len - n);
    } else {
        addDupN_alist(list, 0, n);
        setDupN_alist(list, 0, n, len);
        removeLastN_alist(list, n);
    }
}

void rotateUpN_alist(
    ArrayList list[static const 1],
    uint32_t n
) {
    uint32_t const len = list->len;

    assert(isValid_alist(list));

    if ((n %= len) == 0) {
        /* Do nothing */
    } else if (n >= len >> 1) {
        rotateDownN_alist(list, len - n);
    } else {
        addIndeterminateN_alist(list, n);
        setDupN_alist(list, n, 0, len);
        setDupN_alist(list, 0, len, n);
        removeLastN_alist(list, n);
    }
}

void* setDupN_alist(
    ArrayList list[static const 1],
    uint32_t const dup_id,
    uint32_t const orig_id,
    uint32_t const n
) {
    assert(isValid_alist(list));
    assert(list->len > dup_id);
    assert(list->len > orig_id);
    assert(dup_id != orig_id);
    assert(n <= list->len - dup_id);
    assert(n <= list->len - orig_id);
    assert(n > 0);
    {
        void* const p_dup   = get_alist(list, dup_id);
        void* const p_orig  = get_alist(list, orig_id);
        size_t const sz_p   = list->sz_elem * (size_t)n;
        assert(sz_p < SZSZ_MAX);
        assert(sz_p / list->sz_elem == (size_t)n);
        return memmove(p_dup, p_orig, sz_p);
    }
}

void* setN_alist(
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
        void* const p_dest  = get_alist(list, id);
        size_t const sz_p   = list->sz_elem * (size_t)n;

        assert(sz_p < SZSZ_MAX);
        assert(sz_p / list->sz_elem == (size_t)n);

        if (p == NULL) {
            return memset(p_dest, 0, sz_p);
        } else {
            #ifndef NDEBUG
                size_t const sz_dest = list->sz_elem * (size_t)(list->len - id);
            #endif
            assert(sz_dest < SZSZ_MAX);
            assert(sz_dest / list->sz_elem == (size_t)(list->len - id));
            assert(!overlaps_ptr(p_dest, p, sz_dest, sz_p));

            /* UB if p_dest and p overlap. */
            return memcpy(p_dest, p, sz_p);
        }
    }
}

void swapN_alist(
    ArrayList list[static const 1],
    uint32_t const id1,
    uint32_t const id0,
    uint32_t const n
) {
    uint32_t const len = list->len;

    assert(isValid_alist(list));
    assert(id1 < len);
    assert(id0 < len);
    assert(id1 != id0);
    assert(n <= len - id1);
    assert(n <= len - id0);
    assert(n > 0);

    if (id1 < id0)
        assert(id1 + n <= id0);
    else
        assert(id0 + n <= id1);

    addDupN_alist(list, id0, n);
    setDupN_alist(list, id0, id1, n);
    setDupN_alist(list, id1, len, n);
    removeLastN_alist(list, n);
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

