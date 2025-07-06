#include <assert.h>
#include <string.h>
#include "padkit/chunk.h"
#include "padkit/repeat.h"
#include "padkit/size.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

Item add_chunk(
    Chunk* const chunk,
    void const* const p_item,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    {
        uint32_t const area = AREA_CHUNK(chunk);
        return (Item){
            addN_alist(chunk->items, p_item, sz_item),
            sz_item,
            *(uint32_t*)add_alist(chunk->offsets, &area)
        };
    }
}

void (* const addAll_chunk)(
    Chunk* const head,
    Chunk const* const tail
) = &concat_chunk;

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
        Item const orig_first_item  = get_chunk(chunk, id);
        uint32_t const dup_offset   = AREA_CHUNK(chunk);
        uint32_t const area_items   = (LEN_CHUNK(chunk) - id == n)
            ?                                    dup_offset - orig_first_item.offset
            : *(uint32_t*)get_alist(chunk->offsets, id + n) - orig_first_item.offset;

        assert(area_items < SZ32_MAX - dup_offset);
        {
            Item const dup_first_item = (Item){
                addDupN_alist(chunk->items, orig_first_item.offset, area_items),
                orig_first_item.sz,
                dup_offset
            };
            uint32_t const* itr = get_alist(chunk->offsets, id);
            uint32_t const diff = AREA_CHUNK(chunk) - dup_offset;

            REPEAT(n) {
                uint32_t const new_offset = *itr + diff;
                itr = add_alist(chunk->offsets, &new_offset);
            }

            return dup_first_item;
        }
    }
}

Item addFromStream_chunk(
    Chunk* const chunk,
    FILE* const stream,
    uint32_t const max_sz_item,
    uint32_t const max_sz_buf
) {
    assert(isValid_chunk(chunk));
    assert(stream != NULL);
    assert(max_sz_item > 0);
    assert(max_sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(max_sz_buf > 0);
    assert(max_sz_buf <= max_sz_item);
    {
        uint32_t sz_rem = max_sz_item;
        uint32_t sz_buf = max_sz_buf;
        Item item       = addIndeterminate_chunk(chunk, sz_buf);
        size_t sz_rd    = fread(item.p, 1, sz_buf, stream);
        assert(sz_rd < SZ32_MAX);
        item.sz = (uint32_t)sz_rd;
        sz_rem -= sz_rd;
        while (sz_rd != 0 && sz_rem > 0) {
            sz_buf  = (max_sz_buf < sz_rem) ? max_sz_buf : sz_rem;
            item    = appendIndeterminateLast_chunk(chunk, sz_buf);
            sz_rd   = fread((char*)item.p + item.sz - sz_buf, 1, sz_buf, stream);
            sz_rem -= sz_rd;
        }
        return item;
    }
}

Item addIndeterminateN_chunk(
    Chunk* const chunk,
    uint32_t const n,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(n > 0);
    assert(n < SZ32_MAX);
    assert(LEN_CHUNK(chunk) < SZ32_MAX - n);
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    {
        uint32_t const area = AREA_CHUNK(chunk);
        uint32_t const sz_total = n * sz_item;
        assert(sz_total < SZ32_MAX - area);
        assert(sz_total / n == sz_item);

        addIndeterminateN_alist(chunk->items, sz_total);
        add_alist(chunk->offsets, &area);
        return divideEquallyLast_chunk(chunk, n);
    }
}

Item addZeros_chunk(
    Chunk* const chunk,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    {
        uint32_t const area = AREA_CHUNK(chunk);
        return (Item){
            addZerosN_alist(chunk->items, sz_item),
            sz_item,
            *(uint32_t*)add_alist(chunk->offsets, &area)
        };
    }
}

Item appendDupLast_chunk(
    Chunk* const chunk,
    uint32_t const id
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > id);
    {
        Item const orig_item = get_chunk(chunk, id);
        assert(isValid_item(&orig_item));
        addDupN_alist(chunk->items, orig_item.offset, orig_item.sz);
    }
    return getLast_chunk(chunk);
}

Item appendFromStreamLast_chunk(
    Chunk* const chunk,
    FILE* const stream,
    uint32_t const max_sz_item,
    uint32_t const max_sz_buf
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(stream != NULL);
    assert(max_sz_item > 0);
    assert(max_sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(max_sz_buf > 0);
    assert(max_sz_buf <= max_sz_item);
    addFromStream_chunk(chunk, stream, max_sz_item, max_sz_buf);
    return mergeLastPair_chunk(chunk);
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

    constructEmpty_alist(chunk->offsets, sizeof(uint32_t), init_cap_len);
    constructEmpty_alist(chunk->items, sizeof(char), init_cap_area);
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
    flush_alist(chunk->offsets);
    add_alist(chunk->offsets, 0);
    return getLast_chunk(chunk);
}

Item mergeN_chunk(Chunk* const chunk, uint32_t const first_id, uint32_t const n) {
    assert(isValid_chunk(chunk));
    assert(first_id < LEN_CHUNK(chunk));
    assert(n >= 2);
    assert(first_id + n <= LEN_CHUNK(chunk));
    removeN_alist(chunk->offsets, first_id + 1, n - 1);
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

void vconstruct_chunk(
    void* const p_chunk,
    va_list args
) {
    Chunk* const chunk              = (Chunk*)p_chunk;
    uint32_t const init_cap_len     = va_arg(args, uint32_t);
    uint32_t const init_cap_area    = va_arg(args, uint32_t);
    constructEmpty_chunk(chunk, init_cap_len, init_cap_area);
}
