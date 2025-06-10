#include <assert.h>
#include "padkit/chunk.h"
#include "padkit/repeat.h"
#include "padkit/size.h"

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
            ?                                    area_chunk - orig_first_item.offset
            : *(uint32_t*)get_alist(chunk->offsets, id + n) - orig_first_item.offset;

        assert(area_items < SZ32_MAX - area_chunk);
        {
            Item const dup_first_item = (Item){
                addDupN_alist(chunk->items, orig_first_item.offset, area_items),
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

/*
Item addFromStream_chunk(
    Chunk* const chunk,
    FILE* const stream,
    char const terminals[const],
    uint32_t const nTerminals,
    uint32_t const max_sz_item
) {
    Item item = NOT_AN_ITEM;

    assert(isValid_chunk(chunk));
    assert(stream != NULL);
    assert(terminals == NULL || (0 < nTerminals && nTerminals < SZ32_MAX));
    assert(terminals != NULL || max_sz_item > 0);
    assert(max_sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(max_sz_buf > 0);
    assert(max_sz_buf < SZ32_MAX - AREA_CHUNK(chunk));

    item.offset = *(uint32_t*)add_alist(item->offsets, &AREA_CHUNK(chunk));
    appendFromStreamLast_chunk
}
*/

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

/*
Item appendFromStreamLast_chunk(
    Chunk* const chunk,
    FILE* const stream,
    char const terminals[const],
    uint32_t const nTerminals,
    uint32_t const max_sz_item,
    uint32_t const max_sz_buf
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(stream != NULL);
    assert(terminals == NULL || (0 < nTerminals && nTerminals < SZ32_MAX));
    assert(terminals != NULL || max_sz_item > 0);
    assert(max_sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(max_sz_buf > 0);
    assert(max_sz_buf < SZ32_MAX - AREA_CHUNK(chunk));
    {
        uint32_t sz_total   = 0;
        Item item           = getLast_chunk(chunk);
        bool doContinue     = !feof(stream);
        while (doContinue) {
            uint32_t const sz_remaining = max_sz_item - sz_total;
            uint32_t const sz_read      = (sz_remaining > max_sz_buf) ? max_sz_buf : sz_remaining;
            void* const p_buf           = addIndeterminateN_alist(chunk->items, sz_read);
            size_t const sz_buf         = fread(p_buf, 1, sz_read, stream);
            assert(sz_buf > 0);
            assert(sz_buf < SZ32_MAX);
            assert(sz_read >= (uint32_t)sz_buf);

            sz_total += sz_buf;
            item.sz += sz_buf;

            doContinue &= ((uint32_t)sz_buf == sz_read);
            if (!doContinue)
                deleteLast_alist(chunk->items, sz_read - (uint32_t)sz_buf);

            if (terminals != NULL) {
                char const* itr = terminals;
                REPEAT(nTerminals) {
                    char const* const p_terminal = memchr(p_buf, *itr++, sz_buf);
                    if (p_terminal != NULL) {
                        uint32_t const sz
                    }
                }
            }

            doContinue &= !feof(stream);
        }
        return item;
    }
}
*/

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

        addZerosN_alist(chunk->items, sz_item);
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
    {
        Item first_item         = getLast_chunk(chunk);
        uint32_t const sz_item  = first_item.sz / n;
        uint32_t offset_item    = first_item.offset;

        if (n == 1)
            return first_item;

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

/*
uint32_t divideLast_chunk(
    Chunk* const chunk,
    char const delimeters[],
    uint32_t const nDelimeters
) {
    uint32_t n = 0;

    assert
}
*/

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

void vconstruct_chunk(
    void* const p_chunk,
    va_list args
) {
    Chunk* const chunk              = (Chunk*)p_chunk;
    uint32_t const init_cap_len     = va_arg(args, uint32_t);
    uint32_t const init_cap_area    = va_arg(args, uint32_t);
    constructEmpty_chunk(chunk, init_cap_len, init_cap_area);
}
