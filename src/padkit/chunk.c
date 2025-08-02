#include <assert.h>
#include <string.h>
#include "padkit/chunk.h"
#include "padkit/repeat.h"
#include "padkit/size.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

void (* const addAll_chunk)(
    Chunk* const head,
    Chunk const* const tail,
    uint32_t const n
) = &concatN_chunk;

Item addDupLastN_chunk(
    Chunk* const chunk,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    assert(n < SZ32_MAX - LEN_CHUNK(chunk));
    return addDupN_chunk(chunk, LEN_CHUNK(chunk) - n, n);
}

Item addDupLastSameN_chunk(
    Chunk* const chunk,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(n > 0);
    assert(n < SZ32_MAX - LEN_CHUNK(chunk));
    return addDupSameN_chunk(chunk, LEN_CHUNK(chunk) - 1, n);
}

Item addDupN_chunk(
    Chunk* const chunk,
    uint32_t const id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > id);
    assert(LEN_CHUNK(chunk) - id >= n);
    assert(n > 0);
    {
        Item const first_orig   = getN_chunk(chunk, id);
        uint32_t total_area     = AREA_CHUNK(chunk);
        uint32_t* offset        = addIndeterminateN_alist(chunk->offsets, n);
        for (uint32_t i = id; i < id + n; i++) {
            Item item   = get_chunk(chunk, i);
            *(offset++) = total_area;
            total_area += item.sz;
        }
        addDupN_alist(chunk->items, first_orig->p, total_area - AREA_CHUNK(chunk));
        return getN_chunk(chunk, first_id);
    }
}

Item addDupSameN_chunk(
    Chunk* const chunk,
    uint32_t const id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > id);
    assert(n > 0);
    assert(n < SZ32_MAX - LEN_CHUNK(chunk));
    {
        uint32_t const dup_id   = LEN_CHUNK(chunk);
        Item const orig_item    = get_chunk(chunk, id);
        addIndeterminateN_chunk(chunk, orig_item.sz, n);
        return setDupSameN_chunk(chunk, dup_id, id, n);
    }
}

Item addFN_chunk(
    Chunk* const chunk,
    FILE* const stream,
    uint32_t const max_sz_item,
    uint32_t const max_sz_buf,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(stream != NULL);
    assert(max_sz_item > 0);
    assert(max_sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(max_sz_buf > 0);
    assert(max_sz_buf <= max_sz_item);
    assert(n > 0);
    assert(n < SZ32_MAX - LEN_CHUNK(chunk));
    {
        uint32_t sz_rem = max_sz_item;
        uint32_t sz_buf = max_sz_buf;
        Item item       = addIndeterminate_chunk(chunk, sz_buf);
        size_t sz_rd    = fread(item.p, 1, sz_buf, stream);
        assert(sz_rd < SZ32_MAX);
        item.sz = (uint32_t)sz_rd;
        sz_rem -= sz_rd;
        while (sz_rd != 0 && 0 < sz_rem && sz_rem < SZ32_MAX) {
            sz_buf  = (max_sz_buf < sz_rem) ? max_sz_buf : sz_rem;
            item    = appendIndeterminateLast_chunk(chunk, sz_buf);
            sz_rd   = fread((char*)item.p + item.sz - sz_buf, 1, sz_buf, stream);
            sz_rem -= sz_rd;
            if (sz_rd < sz_buf) item = shrinkLast_chunk(chunk, sz_buf - sz_rd);
        }
        if (n > 1) addDupLastSameN_chunk(chunk, n - 1);
        return item;
    }
}

Item addNEq_chunk(
    Chunk* const chunk,
    void const* const p,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n < SZ32_MAX - LEN_CHUNK(chunk));
    {
        uint32_t const sz_total = sz_item * n;
        assert(sz_total < SZ32_MAX - AREA_CHUNK(chunk));
        assert(sz_total / sz_item == n);
        assert(p == NULL || !overlaps_ptr(chunk->items->array, p, AREA_CHUNK(chunk), sz_total));
        {
            Item const first_item = addIndeterminateN_chunk(chunk, sz_item, n);
            if (p == NULL) return first_item;
            /* UB if chunk->items->array and p overlap. */
            setN_alist(chunk->items, p, sz_total);
            return first_item;
        }
    }
}

Item addSameN_chunk(
    Chunk* const chunk,
    void const* const p_item,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n < SZ32_MAX - LEN_CHUNK(chunk));
    assert(p_item == NULL || !overlaps_ptr(chunk->items->array, p_item, AREA_CHUNK(chunk), sz_item));
    {
        uint32_t const first_offset = AREA_CHUNK(chunk);
        uint32_t const sz_total     = sz_item * n;
        assert(sz_total < SZ32_MAX - AREA_CHUNK(chunk));
        assert(sz_total / sz_item == n);
        {
            char* const first_p = addIndeterminateN_alist(chunk->items, sz_total);
            for (
                uint32_t new_offset = first_offset, *p_offset = addIndeterminateN_alist(chunk->offsets, n);
                new_offset < AREA_CHUNK(chunk);
                new_offset += sz_item, p_offset++;
            ) *p_offset = new_offset;

            if (p_item != NULL) {
                uint32_t sz = sz_item;
                /* UB if p_item overlaps with chunk->items->array. */
                setN_alist(chunk->items, first_offset, p_item, sz);
                while (sz << 1 < sz_total) {
                    setDupN_alist(chunk->items, first_offset + sz, first_offset, sz);
                    sz <<= 1;
                }
                setDupN_alist(chunk->items, first_offset + sz, sz_total - sz);
            }

            return (Item){ first_p, sz_item, first_offset };
        }
    }
}

Item addZerosN_chunk(
    Chunk* const chunk,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n < SZ32_MAX - LEN_CHUNK(chunk));
    {
        uint32_t const first_offset = AREA_CHUNK(chunk);
        uint32_t const sz_total     = sz_item * n;
        assert(sz_total < SZ32_MAX - first_offset);
        assert(sz_total / sz_item == n);
        {
            Item const first_item = addIndeterminateN_chunk(chunk, sz_item, n);
            memset(first_item.p, 0, sz_total);
            return first_item;
        }
    }
}

Item appendAll_chunk(
    Chunk* const chunk,
    void const* const p_item,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(p_item == NULL || !overlaps_ptr(chunk->items->array, p_item, AREA_CHUNK(chunk), sz_item));
    return appendLastN_chunk(chunk, p_item, sz_item, LEN_CHUNK(chunk));
}

Item appendDup_chunk(
    Chunk* const chunk,
    uint32_t const dup_id,
    uint32_t const orig_id
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > dup_id);
    assert(LEN_CHUNK(chunk) > orig_id);
    {
        Item const orig_item = get_chunk(chunk, orig_id);
        dup_item = appendIndeterminate_chunk(chunk, dup_id, orig_item.sz);
        setDupN_alist(chunk->items, dup_item.offset + dup_item.sz - orig_item.sz, orig_item.offset, orig_item.sz);
        return dup_item;
    }
}

Item appendFLastN_chunk(
    Chunk* const chunk,
    FILE* const stream,
    uint32_t const max_sz_item,
    uint32_t const max_sz_buf,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(stream != NULL);
    assert(max_sz_item > 0);
    assert(max_sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(max_sz_buf > 0);
    assert(max_sz_buf <= max_sz_item);
    assert(n > 0);
    assert(n < SZ32_MAX - LEN_CHUNK(chunk));
    addFN_chunk(chunk, stream, max_sz_item, max_sz_buf, n);
    return mergeLastN_chunk(chunk, n + 1);
}

Item appendLast_chunk(
    Chunk* const chunk,
    void const* const p_item,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    addN_alist(chunk->items, p_item, sz_item);
    return getLast_chunk(chunk);
}

Item appendZerosLast_chunk(
    Chunk* const chunk,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    addZerosN_alist(chunk->items, sz_item);
    return getLast_chunk(chunk);
}

void construct_chunk(void* const p_chunk, ...) {
    va_list args;
    va_start(args, p_chunk);
    vconstruct_chunk(p_chunk, args);
    va_end(args);
}

void constructEmpty_chunk(
    Chunk* const chunk,
    uint32_t const init_cap_len,
    uint32_t const init_cap_area
) {
    assert(chunk != NULL);
    assert(!isAllocated_chunk(chunk));
    assert(init_cap_len > 0);
    assert(init_cap_len < SZ32_MAX);
    assert(init_cap_area > 0);
    assert(init_cap_area < SZ32_MAX);

    constructEmpty_alist(chunk->offsets, sizeof(uint32_t), init_cap_len);
    constructEmpty_alist(chunk->items, sizeof(char), init_cap_area);
}

void deleteLastN_chunk(
    Chunk* const chunk,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    if (n == LEN_CHUNK) {
        flush_chunk(chunk);
    } else {
        Item const first_item = get_chunk(chunk, LEN_CHUNK(chunk) - n);
        deleteLastN_alist(chunk->offsets, n);
        deleteLastN_alist(chunk->items, AREA_CHUNK(chunk) - first_item.offset);
    }
}

void deleteN_chunk(
    Chunk* const chunk,
    uint32_t const id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - id);
    if (n == LEN_CHUNK(chunk) - id) {
        deleteLastN(chunk, n);
    } else {
        Item const first_deleted    = get_chunk(chunk, id);
        Item const first_shifted    = get_chunk(chunk, id + n);
        uint32_t const shft         = first_shifted.offset - first_deleted.offset;
        deleteN_alist(chunk->items, id, shft);
        deleteN_alist(chunk->offsets, id, n);
        for (
            uint32_t* offset = get_alist(chunk->offsets, id), cnt = 0;
            cnt < LEN_CHUNK(chunk) - id - n;
            offset++, cnt++
        ) *offset -= shft;
    }
}

void destruct_chunk(void* const p_chunk) {
    Chunk* const chunk = (Chunk*)p_chunk;
    assert(isAllocated_chunk(chunk));
    destruct_alist(chunk->offsets);
    destruct_alist(chunk->items);
    *chunk = NOT_A_CHUNK;
}

Item divideEquallyLast_chunk(
    Chunk* const chunk,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(n > 0);
    if (n == 1) {
        return getLast_chunk(chunk);
    } else {
        Item first_item         = getLast_chunk(chunk);
        uint32_t const sz_item  = first_item.sz / n;
        uint32_t offset_item    = first_item.offset;

        assert(isValid_item(&first_item));
        assert(first_item.sz > n);
        assert(first_item.sz % n == 0);

        first_item.sz = sz_item;
        REPEAT(n - 1) {
            offset_item += sz_item;
            add_alist(chunk->offsets, &offset_item);
        }

        return first_item;
    }
}

uint32_t divideLast_chunk(
    Chunk* const chunk,
    char const delimeters[],
    uint32_t const nDelimeters
) {
    uint32_t n = 1;

    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(delimeters != NULL);
    assert(nDelimeters > 0);
    assert(nDelimeters < SZ32_MAX);
    {
        Item const item = getLast_chunk(chunk);
        char* const p   = item.p;
        assert(isValid_item(&item));

        for (uint32_t i = 0; i < item.sz; i++) {
            bool const isDelimeter = (memchr(delimeters, p[i], nDelimeters) != NULL);
            if (isDelimeter) {
                uint32_t const new_offset = item.offset + i + 1;
                p[i] = '\0';
                add_alist(chunk->offsets, &new_offset);
                n++;
            }
        }
    }
    return n;
}

void flush_chunk(Chunk* const chunk) {
    assert(isValid_chunk(chunk));
    flush_alist(chunk->offsets);
    flush_alist(chunk->items);
}

Item get_chunk(
    Chunk const* const chunk,
    uint32_t const id
) {
    Item item = NOT_AN_ITEM;

    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > id);

    item.offset = *(uint32_t*)get_alist(chunk->offsets, id);
    item.sz     = (LEN_CHUNK(chunk) - 1 == id)
        ? AREA_CHUNK(chunk) - item.offset
        : *(uint32_t*)get_alist(chunk->offsets, id + 1) - item.offset;
    item.p      = get_alist(chunk->items, item.offset);

    return item;
}

Item getLast_chunk(Chunk const* const chunk) {
    Item item = NOT_AN_ITEM;

    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);

    item.offset = *(uint32_t*)getLast_alist(chunk->offsets);
    item.sz     = AREA_CHUNK(chunk) - item.offset;
    item.p      = (item.sz == 0)
        ? getLast_alist(chunk->items)
        : getLastN_alist(chunk->items, item.sz);

    return item;
}

bool isAllocated_chunk(void const* const p_chunk) {
    Chunk const* const chunk = (Chunk const*)p_chunk;

    if (chunk == NULL) {
        return 0;
    } else if (!isAllocated_alist(chunk->offsets)) {
        assert(!isAllocated_alist(chunk->items));
        return 0;
    } else {
        assert(isAllocated_alist(chunk->items));
        return 1;
    }
}

bool isValid_chunk(void const* const p_chunk) {
    Chunk const* const chunk = (Chunk const*)p_chunk;

    if (chunk == NULL)                  return 0;
    if (!isValid_alist(chunk->offsets)) return 0;
    if (!isValid_alist(chunk->items))   return 0;

    return 1;
}

Item mergeAll_chunk(Chunk* const chunk) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) >= 2);
    flush_alist(chunk->offsets);
    addZeros_alist(chunk->offsets);
    return getLast_chunk(chunk);
}

Item mergeLastN_chunk(
    Chunk* const chunk,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(n >= 2);
    assert(n <= LEN_CHUNK(chunk));
    if (n == LEN_CHUNK)
        return mergeAll_chunk(chunk);
    else
        deleteLastN_alist(chunk->offsets, n - 1);
    return getLast_chunk(chunk);
}

Item mergeN_chunk(Chunk* const chunk, uint32_t const first_id, uint32_t const n) {
    assert(isValid_chunk(chunk));
    assert(first_id < LEN_CHUNK(chunk));
    assert(n >= 2);
    assert(first_id + n <= LEN_CHUNK(chunk));
    if (first_id + n == LEN_CHUNK(chunk))
        return mergeLastN_chunk(chunk, n);
    else
        deleteN_alist(chunk->offsets, first_id + 1, n - 1);
    return get_chunk(chunk, first_id);
}

Item mergeLastPair_chunk(Chunk* const chunk) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) >= 2);
    pop_alist(chunk->offsets);
    return getLast_chunk(chunk);
}

Item mergePair_chunk(Chunk* const chunk, uint32_t const first_id) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > first_id + 1);
    remove_alist(chunk->offsets, first_id + 1);
    return get_chunk(chunk, first_id);
}

Item (* const peek_chunk)(Chunk const* const chunk) = &getLast_chunk;

Item (* const pop_chunk)(Chunk* const chunk) = &removeLast_chunk;

Item (* const push_chunk)(
    Chunk* const chunk,
    void const* const p_item,
    uint32_t const sz_item
) = &add_chunk;

Item shrinkAll_chunk(
    Chunk* const chunk,
    uint32_t const by
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(by > 0);
    assert(by < SZ32_MAX);
    return shrinkLastN_chunk(chunk, by, LEN_CHUNK(chunk));
}

Item shrinkLast_chunk(
    Chunk* const chunk,
    uint32_t const by
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(by > 0);
    assert(by < AREA_CHUNK(chunk));
    {
        Item last_item = getLast_chunk(chunk);
        assert(by < last_item.sz);
        deleteLastN_alist(chunk->items, by);
        last_item.sz -= by;
        return last_item;
    }
}

Item shrinkLastN_chunk(
    Chunk* const chunk,
    uint32_t const by,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(by > 0);
    assert(by < AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    {
        Item item = shrinkLast_chunk(chunk, by);
        for (i = LEN_CHUNK(chunk) - 1; i > LEN_CHUNK(chunk) - n; item = get_chunk(chunk, --i)) {
            uint32_t const shft = AREA_CHUNK(chunk) - item.offset;
            assert(item.offset > by);
            item.offset -= by;
            set_alist(chunk->offsets, i, &(item.offset));
            setDupN_alist(chunk->items, item.offset, item.offset + by, shft);
        }
        return item;
    }
}

Item shrinkN_chunk(
    Chunk* const chunk,
    uint32_t const id,
    uint32_t const by,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(by > 0);
    assert(by < AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - id);
    if (id + n == LEN_CHUNK(chunk)) {
        return shrinkLastN_chunk(chunk, by, n);
    } else {
        uint32_t shft   = 0;
        Item item       = NOT_AN_ITEM;
        for (uint32_t i = id + n; i > id; i--) {
            item = get_chunk(chunk, i);
            shft = AREA_CHUNK(chunk) - item.offset;
            assert(item.offset > by);
            item.offset -= by;
            set_alist(chunk->offsets, i, &(item.offset));
            setDupN_alist(chunk->items, item.offset, item.offset + by, shft);
        }
        return item;
    }
}

void swapN_chunk(
    Chunk* const chunk,
    uint32_t const id1,
    uint32_t const id0,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(id1 < LEN_CHUNK(chunk));
    assert(id0 < LEN_CHUNK(chunk));
    assert(id1 != id0);
    assert(n > 0);
    assert(n < LEN_CHUNK(chunk));
    assert(id1 + n <= LEN_CHUNK(chunk));
    assert(id0 + n <= LEN_CHUNK(chunk));
    for (uint32_t i = id0, j = id1; i < id0 + n; i++, j++) {
        addDup_chunk(chunk, i);
        setDup_chunk(chunk, j, i);
        setDup_chunk(chunk, LEN_CHUNK(chunk) - 1, j);
        deleteLast(chunk);
    }
}

void vconstruct_chunk(
    void* const p_chunk,
    va_list args
) {
    Chunk* const chunk              = (Chunk*)p_chunk;
    uint32_t const init_cap_len     = va_arg(args, uint32_t);
    uint32_t const init_cap_area    = va_arg(args, uint32_t);
    constructEmpty_chunk(chunk, init_cap_len, init_cap_area);
}
