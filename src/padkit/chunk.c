#include <assert.h>
#include "padkit/chunk.h"

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
        uint32_t const area_chunk   = AREA_CHUNK(chunk);
        uint32_t const area_items   = (LEN_CHUNK(chunk) - id == n)
            ?                                    area_chunk - orig_first_item.offset;
            : *(uint32_t*)get_alist(chunk->offsets, id + n) - orig_first_item.offset;

        assert(area_items < SZ32_MAX - area_chunk);

        {
            Item const dup_first_item = (Item){
                addDupN_alist(chunk->items, orig_first_item.offset, area_items);
                orig_first_item.sz,
                area_chunk
            };
            uint32_t const* itr = get_alist(chunk->offsets, id);
            uint32_t const diff = area_chunk - dup_first_item.offset;

            REPEAT(n) {
                uint32_t const new_offset = *itr++ + diff;
                add_alist(chunk->offsets, &new_offset);
            }

            return dup_first_item;
        }
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
            addZerosN_alist(chunk->items, p_item, sz_item),
            sz_item,
            *(uint32_t*)add_alist(chunk->offsets, &area)
        };
    }
}

Item addZerosN_chunk(
    Chunk* const chunk,
    uint32_t const n,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > n);
    assert(n > 0);
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    {
        uint32_t const sz_total = n * sz_item;
        assert(sz_total < SZ32_MAX - AREA_CHUNK(chunk));
        assert(sz_total / n == sz_item);

        addZeros_chunk(chunk, sz_total);
        return divideEquallyLast_chunk(chunk, n);
    }
}

Item appendDupLast_chunk(
    Chunk* const chunk,
    uint32_t const id
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > id);
    {
        Item const orig_item    = get_chunk(chunk, id);
        Item dup_item           = getLast_chunk(chunk);

        addDupN_alist(chunk->items, orig_item.offset, orig_item.sz);
        dup_item.sz += orig_item.sz;

        return dup_item;
    }
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
    {
        Item item = getLast_chunk(chunk);

        addN_alist(chunk->items, p_item, sz_item);
        item.sz += sz_item;

        return item;
    }
}

Item appendZerosLast_chunk(
    Chunk* const chunk,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    {
        Item item = getLast_chunk(chunk);

        addZerosN_alist(chunk->items, p_item, sz_item);
        item.sz += sz_item;

        return item;
    }
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

    constructEmpty_alist(chunk->offsets, init_cap_len);
    constructEmpty_alist(chunk->items, init_cap_area);
}

void destruct_chunk(void* const p_chunk) {
    Chunk* const chunk = (Chunk*)p_chunk;
    assert(isAllocated_chunk(chunk));
    destruct_alist(chunk->offsets);
    destruct_alist(chunk->items);
    *chunk = NOT_A_CHUNK;
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
    item.p      = get_alist(chunk->items, item->offset);

    return item;
}

Item getLast_chunk(Chunk const* const chunk) {
    Item item = NOT_AN_ITEM;

    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);

    item.offset = *(uint32_t)getLast_alist(chunk->offsets);
    item.sz     = AREA_CHUNK(chunk) - item.offset;
    item.p      = getLastN_alist(chunk->items, item.sz);

    return item;
}

bool isAllocated_chunk(void const* const p_chunk) {
    Chunk const* const chunk = (Chunk)p_chunk;

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
    Chunk const* const chunk = (Chunk)p_chunk;

    if (chunk == NULL)                  return 0;
    if (!isValid_alist(chunk->offsets)) return 0;
    if (!isValid_alist(chunk->items))   return 0;

    return 1;
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
