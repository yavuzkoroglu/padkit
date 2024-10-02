#include <assert.h>
#include <string.h>
#include "padkit/chunk.h"
#include "padkit/invalid.h"
#include "padkit/repeat.h"
#include "padkit/size.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

static char const defaultDelimeters[] = {' ', '\t', '\n', '\v', '\f', '\r', '\0'};

Item addIndeterminate_chunk(
    Chunk chunk,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));

    return addItem_chunk(chunk, sz_item, NULL);
}

Item addItem_chunk(
    Chunk chunk,
    void const* const p_item,
    uint32_t const sz_item
) {
    Item item;

    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));

    #ifndef NDEBUG
        if (sz_item > chunk[0].cap - chunk[0].len)
            assert(!overlaps_ptr(chunk[0].arr, p_item, chunk[0].cap, sz_item));
    #endif

    item.sz     = sz_item;
    item.offset = AREA_CHUNK;

    /* Invalidates p_item if sz_item > chunk->cap - chunk->len and chunk->arr overlaps with p_item */
    item.p      = addN_alist(&chunk[0], p_item, sz_item);

    add_alist(&chunk[1], &item.offset);

    return item;
}

Item append_chunk(
    Chunk chunk,
    void const* const p_item,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));

    if (LEN_CHUNK(chunk) == 0) {
        return addItem_chunk(chunk, sz_item, p_item);
    } else {
        addN_alist(&chunk[0], p_item, sz_item);
        return getLast_chunk(chunk);
    }
}

Item appendDuplicate_chunk(
    Chunk chunk,
    uint32_t const id
) {
    Item last_item = getLast_chunk(chunk);

    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > id);
    assert(AREA_CHUNK(chunk) > last_item.offset);

    if (1 == LEN_CHUNK(chunk) - id) {
        uint32_t const area = AREA_CHUNK(chunk) - last_item.offset;
        addDupN_alist(&chunk[0], last_item.offset, area);
        last_item.sz += last_item.sz;
    } else {
        uint32_t const* const offsets[2] = {
            get_alist(&chunk[1], id),
            get_alist(&chunk[1], id + 1)
        };
        uint32_t const area = *offsets[1] - *offsets[0];
        addDupN_alist(&chunk[0], *offsets[0], area);
        last_item.sz += last_item.sz;
    }
    return last_item;
}

void concat_chunk(
    Chunk head,
    Chunk const tail
) {
    uint32_t const head_area = AREA_CHUNK(head);
    #ifndef NDEBUG
        uint32_t const tail_area = AREA_CHUNK(tail);
    #endif

    assert(isValid_chunk(head));
    assert(isValid_chunk(tail));
    assert(!overlaps_ptr(head[0].arr, tail[0].arr, head_area, tail_area));

    concat_alist(&head[0], &tail[0]);

    {
        uint32_t const* old_offset = getFirst_alist(&tail[1]);
        REPEAT(LEN_CHUNK(tail)) {
            uint32_t const new_offset = *old_offset + head_area;
            add_alist(&head[1], &new_offset);
            old_offset++;
        }
    }
}

void construct_chunk(void* const p_chunk, ...) {
    va_list args;
    va_start(args, p_chunk);
    vconstruct_chunk(p_chunk);
}

void constructEmpty_chunk(
    Chunk chunk,
    uint32_t const initial_cap_area,
    uint32_t const initial_cap_len
) {
    assert(initial_cap_area > 0);
    assert(initial_cap_area < SZ32_MAX);
    assert(initial_cap_len > 0);
    assert(initial_cap_len < SZ32_MAX);

    constructEmpty_alist(&chunk[0], 1, initial_cap_area);
    constructEmpty_alist(&chunk[1], sizeof(uint32_t), initial_cap_len);
}

void deleteItem_chunk(
    Chunk chunk,
    uint32_t const id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > id);
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - id);

    if (n == LEN_CHUNK(chunk) - id) {
        deleteLast_chunk(chunk, n);
    } else {
        uint32_t const* const offsets[2] = {
            get_alist(&chunk[1], id),
            get_alist(&chunk[1], id + n)
        };
        uint32_t const area = *offsets[1] - *offsets[0];
        assert(area < AREA_CHUNK(chunk));

        delete_alist(&chunk[0], *offsets[0], area);
        delete_alist(&chunk[1], id, n);

        {
            uint32_t* offset = get_alist(&chunk[1], id);
            REPEAT(LEN_CHUNK(chunk) - i) {
                assert(*offset >= area);
                *offset -= area;
                offset++;
            }
        }
    }
}

void deleteLast_chunk(
    Chunk chunk,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));

    if (n == LEN_CHUNK(chunk)) {
        flush_chunk(chunk);
    } else {
        uint32_t const* const offset = getLastN_alist(&chunk[1], n);
        assert(AREA_CHUNK(chunk) >= *offset);

        removeLastN_alist(&chunk[0], AREA_CHUNK(chunk) - *offset);
        removeLastN_alist(&chunk[1], n);
    }
}

void* duplicateItem_chunk(Chunk chunk, uint32_t const id) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    {
        uint32_t const sz_item  = sz_item_chunk(chunk, id);
        void* const new_item    = addIndeterminateItem_chunk(chunk, sz_item);
        void const* const item  = get_chunk(chunk, id);

        return memcpy(new_item, item, sz_item);
    }
}

void* duplicateItemLast_chunk(Chunk chunk) {
    assert(isValid_chunk(chunk));
    {
        uint32_t const sz_item  = sz_itemLast_chunk(chunk);
        void* const new_item    = addIndeterminateItem_chunk(chunk, sz_item);
        void const* const item  = getLast_chunk(chunk);

        return memcpy(new_item, item, sz_item);
    }
}

void* enlargeItem_chunk(Chunk chunk, uint32_t const id, uint32_t const by) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(by > 0);
    assert(by < SZ32_MAX);

    if (id == LEN_CHUNK(chunk) - 1)
        return enlargeItemLast_chunk(chunk, by);

    addIndeterminate_alist(chunk, by);
    {
        uint32_t const* const offset    = get_alist(chunk + 1, id + 1);
        char* const p                   = get_alist(chunk, *offset);
        uint32_t const sz_move          = AREA_CHUNK(chunk) - *offset;
        assert(AREA_CHUNK(chunk) > *offset);
        memmove(p + by, p, sz_move);
    }
    for (uint32_t i = id + 1; i < LEN_CHUNK(chunk); i++) {
        uint32_t const* const old_offset    = get_alist(chunk + 1, i);
        uint32_t const new_offset           = *old_offset + by;
        set_alist(chunk + 1, i, 1, &new_offset);
    }

    return get_chunk(chunk, id);
}

void* enlargeItemLast_chunk(Chunk chunk, uint32_t const by) {
    assert(isValid_chunk(chunk));
    assert(by > 0);
    assert(by < SZ32_MAX);
    addIndeterminate_alist(chunk, by);
    return getLast_chunk(chunk);
}

void flush_chunk(Chunk chunk) {
    assert(isValid_chunk(chunk));

    flush_alist(chunk);
    flush_alist(chunk + 1);
}

void free_chunk(Chunk chunk) {
    assert(isValid_chunk(chunk));

    free_alist(chunk);
    free_alist(chunk + 1);
}

uint32_t fromStream_chunk(
    Chunk chunk, FILE stream[static const 1],
    char const delimeters[], size_t nDelimeters
) {
    assert(isValid_chunk(chunk));

    if (fromStreamAsWhole_chunk(chunk, stream) == NULL) {
        return INVALID_UINT32;
    } else {
        uint32_t const nTokens = splitLast_chunk(chunk, delimeters, nDelimeters);
        if (nTokens == 0)
            return INVALID_UINT32;
        else
            return LEN_CHUNK(chunk) - nTokens;
    }
}

void* fromStreamAsWhole_chunk(Chunk chunk, FILE stream[static const 1]) {
    assert(isValid_chunk(chunk));

    if (fseek(stream, 0L, SEEK_END) != 0) {
        return NULL;
    } else {
        long const size = ftell(stream);
        if (size < 0L) {
            return NULL;
        #if ULONG_MAX >= UINT32_MAX
            } else if ((unsigned long)size >= SZ32_MAX) {
                return NULL;
        #endif
        #if ULONG_MAX >= SIZE_MAX
            } else if ((unsigned long)size >= SZSZ_MAX) {
                return NULL;
        #endif
        } else if (fseek(stream, 0L, SEEK_SET) != 0) {
            return NULL;
        } else {
            void* const dest = addIndeterminateItem_chunk(chunk, (uint32_t)size);
            if (fread(dest, (size_t)size, 1, stream) == 1)
                return dest;
            else
                return NULL;
        }
    }
}

void* get_chunk(Chunk const chunk, uint32_t const id) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));

    return get_alist(chunk, *(uint32_t*)get_alist(chunk + 1, id));
}

void* getLast_chunk(Chunk const chunk) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);

    return get_chunk(chunk, LEN_CHUNK(chunk) - 1);
}

bool isValid_chunk(Chunk const chunk) {
    if (!isValid_alist(chunk))                      return 0;
    if (!isValid_alist(chunk + 1))                  return 0;
    if (chunk[0].sz_element != 1)                   return 0;
    if (chunk[1].sz_element != sizeof(uint32_t))    return 0;
    if (LEN_CHUNK(chunk) > AREA_CHUNK(chunk))       return 0;

    return 1;
}

void* resizeItem_chunk(Chunk chunk, uint32_t const id, uint32_t const sz_new) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(sz_new > 0);
    assert(sz_new < SZ32_MAX);
    {
        uint32_t const sz_old = sz_item_chunk(chunk, id);
        assert(sz_new != sz_old);

        if (sz_old > sz_new)
            return shrinkItem_chunk(chunk, id, sz_old - sz_new);
        else
            return enlargeItem_chunk(chunk, id, sz_new - sz_old);
    }
}

void* resizeItemLast_chunk(Chunk chunk, uint32_t const sz_new) {
    assert(isValid_chunk(chunk));
    assert(sz_new > 0);
    assert(sz_new < SZ32_MAX);
    {
        uint32_t const sz_old = sz_itemLast_chunk(chunk);
        assert(sz_new != sz_old);

        if (sz_old > sz_new)
            return shrinkItemLast_chunk(chunk, sz_old - sz_new);
        else
            return enlargeItemLast_chunk(chunk, sz_new - sz_old);
    }
}

void* setItem_chunk(
    Chunk chunk, uint32_t const id,
    uint32_t const sz, void const* const ptr
) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(sz > 0);
    assert(sz < SZ32_MAX);
    assert(ptr != NULL);
    {
        uint32_t const sz_old   = sz_item_chunk(chunk, id);
        void* const dest        = (sz_old == sz) ? get_chunk(chunk, id) : resizeItem_chunk(chunk, id, sz);
        return memcpy(dest, ptr, sz);
    }
}

void* setItemLast_chunk(Chunk chunk, uint32_t const sz, void const* const ptr) {
    assert(isValid_chunk(chunk));
    assert(sz > 0);
    assert(sz < SZ32_MAX);
    assert(ptr != NULL);
    {
        uint32_t const sz_old   = sz_itemLast_chunk(chunk);
        void* const dest        = (sz_old == sz) ? getLast_chunk(chunk) : resizeItemLast_chunk(chunk, sz);
        return memcpy(dest, ptr, sz);
    }
}

void* shrinkItem_chunk(Chunk chunk, uint32_t const id, uint32_t const by) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(by > 0);
    assert(by < SZ32_MAX);

    if (id == LEN_CHUNK(chunk) - 1) {
        return shrinkItemLast_chunk(chunk, by);
    } else {
        uint32_t const* const offset = get_alist(chunk + 1, id + 1);
        assert(AREA_CHUNK(chunk) > *offset);
        delete_alist(chunk, *offset - by, by);
    }

    for (uint32_t i = id + 1; i < LEN_CHUNK(chunk); i++) {
        uint32_t const* const old_offset    = get_alist(chunk + 1, i);
        uint32_t const new_offset           = *old_offset - by;
        assert(*old_offset > by);
        set_alist(chunk + 1, i, 1, &new_offset);
    }

    return get_chunk(chunk, id);
}

void* shrinkItemLast_chunk(Chunk chunk, uint32_t const by) {
    assert(isValid_chunk(chunk));
    assert(by > 0);
    assert(by < SZ32_MAX);
    removeLast_alist(chunk, by);
    return getLast_chunk(chunk);
}

uint32_t splitLast_chunk(Chunk chunk, char const delimeters[], size_t nDelimeters) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);

    if (delimeters == NULL) {
        delimeters  = defaultDelimeters;
        nDelimeters = sizeof(defaultDelimeters);
    }

    assert(nDelimeters > 0);
    assert(nDelimeters < SZSZ_MAX);

    {
        uint32_t const* const old_offset    = getLast_alist(chunk + 1);
        char* const item                    = getLast_chunk(chunk);
        uint32_t const sz                   = sz_itemLast_chunk(chunk);
        uint32_t i                          = 0;
        uint32_t n                          = 0;

        while (i < sz && memchr(delimeters, item[i], nDelimeters) != NULL)
            i++;

        if (i < sz) {
            uint32_t new_offset = *old_offset + i;
            assert(new_offset < AREA_CHUNK(chunk));

            n++;
            set_alist(chunk + 1, LEN_CHUNK(chunk) - 1, 1, &new_offset);

            while (i < sz && memchr(delimeters, item[i], nDelimeters) == NULL)
                i++;

            while (i < sz && memchr(delimeters, item[i], nDelimeters) != NULL)
                i++;

            while (i < sz) {
                new_offset = *old_offset + i;
                assert(new_offset < AREA_CHUNK(chunk));

                n++;
                add_alist(chunk + 1, 1, &new_offset);

                while (i < sz && memchr(delimeters, item[i], nDelimeters) == NULL)
                    i++;

                while (i < sz && memchr(delimeters, item[i], nDelimeters) != NULL)
                    i++;
            }
        }

        while (i > 0 && memchr(delimeters, item[i - 1], nDelimeters) != NULL)
            i--;

        AREA_CHUNK(chunk) = *old_offset + i;

        if (i == 0) {
            n--;
            removeLast_alist(chunk + 1, 1);
        }

        return n;
    }
}

uint32_t sz_item_chunk(Chunk const chunk, uint32_t const id) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));

    if (id == LEN_CHUNK(chunk) - 1) {
        return sz_itemLast_chunk(chunk);
    } else {
        uint32_t const* const offsets[2] = {
            get_alist(chunk + 1, id),
            get_alist(chunk + 1, id + 1),
        };
        assert(offsets[1][0] >= offsets[0][0]);

        return offsets[1][0] - offsets[0][0];
    }
}

uint32_t sz_itemLast_chunk(Chunk const chunk) {
    assert(isValid_chunk(chunk));
    {
        uint32_t const* const offset = getLast_alist(chunk + 1);
        assert(AREA_CHUNK(chunk) >= *offset);

        return AREA_CHUNK(chunk) - *offset;
    }
}

void vconstruct_chunk(
    void* const p_chunk,
    va_list args
) {
    ChunkItr const chunk            = (ChunkItr)p_chunk;
    uint32_t const initial_cap_area = va_arg(args, uint32_t);
    uint32_t const initial_cap_len  = va_arg(args, uint32_t);
    va_end(args);

    constructEmpty_chunk(chunk, initial_cap_area, initial_cap_len);
}
