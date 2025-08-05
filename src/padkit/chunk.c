#include <assert.h>
#include <string.h>
#include "padkit/chunk.h"
#include "padkit/repeat.h"
#include "padkit/size.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

void (* const addAllN_chunk)(
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

Item addN_chunk(
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
                if (sz_total > sz)
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
    return appendSameN_chunk(chunk, 0, p_item, sz_item, LEN_CHUNK(chunk));
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
        Item orig_item      = get_chunk(chunk, orig_id);
        Item const dup_item = appendIndeterminate_chunk(chunk, dup_id, orig_item.sz);
        orig_item.offset += (orig_id > dup_id) * orig_item.sz;
        setDupN_alist(chunk->items, dup_item.offset + dup_item.sz - orig_item.sz, orig_item.offset, orig_item.sz);
        return dup_item;
    }
}

Item appendDupAll2One_chunk(
    Chunk* const chunk,
    uint32_t const dup_id
) {
    assert(isValid_chunk(chunk));
    assert(dup_id < LEN_CHUNK(chunk));
    return appendDupNMany2One_chunk(chunk, dup_id, 0, LEN_CHUNK(chunk));
}

Item appendDupNMany2Many_chunk(
    Chunk* const chunk,
    uint32_t const dup_id,
    uint32_t const orig_id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(dup_id < LEN_CHUNK(chunk));
    assert(orig_id < LEN_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - dup_id);
    assert(n <= LEN_CHUNK(chunk) - orig_id);
    {
        uint32_t const e        = (orig_id > dup_id);
        uint32_t const sz_total = areaBtw_chunk(chunk, orig_id, orig_id + n);
        addIndeterminateN_alist(chunk->items, sz_total);
        deleteLastN_alist(chunk->items, sz_total);
        for (uint32_t i = orig_id, j = dup_id; i < orig_id + n; i++, j++) {
            Item orig_item      = get_chunk(chunk, i);
            Item const dup_item = appendIndeterminate_chunk(chunk, j, orig_item.sz);
            orig_item.offset += e * orig_item.sz;
            setDupN_alist(chunk->items, dup_item.offset + dup_item.sz - orig_item.sz, orig_item.offset, orig_item.sz);
            return dup_item;
        }
    }
}

Item appendDupNMany2One_chunk(
    Chunk* const chunk,
    uint32_t const dup_id,
    uint32_t const orig_id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(dup_id < LEN_CHUNK(chunk));
    assert(orig_id < LEN_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - orig_id);
    {
        uint32_t const sz_total = areaBtw_chunk(chunk, orig_id, orig_id + n);
        Item const orig_first   = getN_chunk(chunk, orig_id);
        Item const tmp          = addIndeterminate_chunk(chunk, sz_total);
        setDupN_alist(chunk->items, tmp.offset, orig_first.offset, sz_total);
    }
    appendDup_chunk(chunk->items, dup_id, LEN_CHUNK(chunk) - 1);
    deleteLast_chunk(chunk);
    return get_chunk(chunk, dup_id);
}

Item appendDupNOne2Many_chunk(
    Chunk* const chunk,
    uint32_t const dup_id,
    uint32_t const orig_id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(dup_id < LEN_CHUNK(chunk));
    assert(orig_id < LEN_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - dup_id);
    {
        Item const orig_item    = get_chunk(chunk, orig_id);
        uint32_t const sz_total = orig_item.sz * n;
        assert(sz_total < SZ32_MAX - AREA_CHUNK(chunk));
        assert(sz_total / orig_item.sz == n);

        appendIndeterminateLastN_chunk(chunk, sz_total);
        {
            Item const tmp = addDup_chunk(chunk, orig_id);
            for (uint32_t i = LEN_CHUNK(chunk) - 2; i > dup_id; i--) {
                uint32_t const shft = (i < orig_id + n) ? (i - orig_id) * sz_item : sz_total;
                Item item           = get_chunk(chunk, i);
                setDupN_alist(chunk->items, item.offset + shft, item.offset, item.sz);
                item.offset += shft;
                set_alist(chunk->offsets, i, &item.offset);
            }
            for (uint32_t i = dup_id; i < dup_id + n; i++) {
                Item item = get_chunk(chunk, i);
                setDupN_alist(chunk->items, item.offset + item.sz - orig_item.sz, tmp.offset, orig_item.sz);
            }
        }
    }
    deleteLast_chunk(chunk);
    return getN_chunk(chunk, dup_id, n);
}

Item appendDupOne2All_chunk(
    Chunk* const chunk,
    uint32_t const orig_id
) {
    assert(isValid_chunk(chunk));
    assert(orig_id < LEN_CHUNK(chunk));
    return appendDupNOne2Many_chunk(chunk, 0, orig_id, LEN_CHUNK(chunk));
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

Item appendLastN_chunk(
    Chunk* const chunk,
    void const* const p_item,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    assert(p_item == NULL || !overlaps_ptr(chunk->items->array, p_item, AREA_CHUNK(chunk), sz_item));
    /* UB if chunk->items->array and p_item overlap. */
    return appendN_chunk(chunk, LEN_CHUNK(chunk) - n, p_item, sz_item, n);
}

Item appendLastSameN_chunk(
    Chunk* const chunk,
    void const* const p_item,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    assert(p_item == NULL || !overlaps_ptr(chunk->items->array, p_item, AREA_CHUNK(chunk), sz_item));
    /* UB if chunk->items->array and p_item overlap. */
    return appendSameN_chunk(chunk, LEN_CHUNK(chunk) - n, p_item, sz_item, n);
}

Item appendN_chunk(
    Chunk* const chunk,
    uint32_t const id,
    void const* const p_item,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - id);
    assert(p_item == NULL || !overlaps_ptr(chunk->items->array, p_item, AREA_CHUNK(chunk), sz_item));
    {
        uint32_t sz_total = sz_item * n;
        assert(sz_total < SZ32_MAX - AREA_CHUNK(chunk));
        assert(sz_total / sz_item == n);
        addIndeterminateN_alist(chunk->items, sz_total);
        for (uint32_t i = LEN_CHUNK(chunk) - 1; i > id; i--) {
            uint32_t const shft = (i < id + n) ? (i - id) * sz_item : sz_total;
            Item item           = get_chunk(chunk, i);
            setDupN_alist(chunk->items, item.offset + shft, item.offset, item.sz);
            item.offset += shift;
            set_alist(chunk->offsets, i, &item.offset);
        }
        for (uint32_t i = id; i < id + n; i++) {
            Item item = get_chunk(chunk, i);
            /* UB if chunk->items->array and p overlap. */
            setN_alist(chunk->items, item.offset + item.sz, p_item, sz_item);
        }
    }
    return getN_chunk(chunk, id);
}

Item appendSameN_chunk(
    Chunk* const chunk,
    uint32_t const id,
    void const* const p_item,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n < SZ32_MAX);
    assert(p_item == NULL || !overlaps_ptr(chunk->items->array, p_item, AREA_CHUNK(chunk), sz_item));
    {
        uint32_t sz_total = sz_item * n;
        assert(sz_total < SZ32_MAX - AREA_CHUNK(chunk));
        assert(sz_total / sz_item == n);
        addIndeterminateN_alist(chunk->items, sz_total);
        {
            Item item = get_chunk(chunk, id);
            setDupN_alist(chunk->items, item.offset + item.sz, item.offset + item.sz + sz_total, sz_total);
            {
                uint32_t sz = sz_item;
                /* UB if chunk->items->array and p_item overlap. */
                setN_alist(chunk->items, item.offset + item.sz, p_item, sz);
                while (sz << 1 < sz_total) {
                    setDupN_alist(chunk->items, item.offset + item.sz + sz, item.offset + item.sz, sz);
                    sz <<= 1;
                }
                if (sz_total > sz)
                    setDupN_alist(chunk->items, item.offset + item.sz + sz, item.offset + item.sz, sz_total - sz);
            }
            for (uint32_t i = id + 1; i < LEN_CHUNK(chunk); i++) {
                uint32_t const new_offset = offsetOf_chunk(chunk, i) + sz_total;
                set_alist(chunk->offsets, &new_offset);
            }
            item.sz += sz_total;
            return item;
        }
    }
}

Item appendZerosAll_chunk(
    Chunk* const chunk,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    return appendZerosN_chunk(chunk, 0, sz_item, LEN_CHUNK(chunk));
}

Item appendZerosLastN_chunk(
    Chunk* const chunk,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    return appendZerosN_chunk(chunk, LEN_CHUNK(chunk) - n, sz_item, n - 1);
}

Item appendZerosN_chunk(
    Chunk* const chunk,
    uint32_t const id,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX - AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - id);
    appendIndeterminateN_chunk(chunk, id, sz_item, n);
    for (uint32_t i = id; i < id + n; i++) {
        Item const item = get_chunk(chunk, i);
        memset(item.p + item.sz - sz_item, 0, sz_item);
    }
    return getN_chunk(chunk, id, n);
}

uint32_t areaBtw_chunk(
    Chunk const* const chunk,
    uint32_t const id0,
    uint32_t const id1
) {
    assert(isValid_chunk(chunk));
    assert(id0 < LEN_CHUNK(chunk));
    assert(id1 <= LEN_CHUNK(chunk));

    if (id0 == id1) {
        return 0;
    } else {
        uint32_t const id_max = (id0 > id1) ? id0 : id1;
        uint32_t const id_min = (id0 < id1) ? id0 : id1;
        if (id_max == LEN_CHUNK(chunk))
            return AREA_CHUNK(chunk) - offsetOf_chunk(chunk, id_min);
        else
            return offsetOf_chunk(chunk, id_max) - offsetOf_chunk(chunk, id_min);
    }
}

uint32_t areaLastN_chunk(
    Chunk const* const chunk,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    return areaBtw_chunk(chunk, LEN_CHUNK(chunk) - n, LEN_CHUNK(chunk));
}

void concatN_chunk(
    Chunk* const head,
    Chunk const* const tail,
    uint32_t const n
) {
    assert(isValid_chunk(head));
    assert(isValid_chunk(tail));
    assert(n > 0);
    assert(n < SZ32_MAX);
    if (LEN_CHUNK(tail) == 0) return;

    {
        uint32_t const sz_tail_total = AREA_CHUNK(tail) * n;
        assert(sz_tail_total < SZ32_MAX - AREA_CHUNK(head));
        assert(sz_tail_total / AREA_CHUNK(tail) == n);

        addIndeterminateN_alist(head->items, sz_tail_total);
        deleteLastN_alist(head->items, sz_tail_total);
        for (uint32_t i = 0; i < LEN_CHUNK(tail); i++) {
            Item const item = get_chunk(tail, i);
            add_chunk(head, item.p, item.sz);
        }
        {
            uint32_t nElements      = LEN_CHUNK(tail);
            uint32_t const nTotal   = nElements * n;
            while (nElements << 1 < nTotal) {
                addDupLastN_chunk(head, nElements);
                nElements <<= 1;
            }
            if (nTotal - nElements > 0)
                addDupLastN_chunk(head, nTotal - nElements);
        }
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
    assert(init_cap_len > 0);
    assert(init_cap_len < SZ32_MAX);
    assert(init_cap_area > 0);
    assert(init_cap_area < SZ32_MAX);

    constructEmpty_alist(chunk->offsets, sizeof(uint32_t), init_cap_len);
    constructEmpty_alist(chunk->items, sizeof(char), init_cap_area);
}

Item cutNEquallyLastN_chunk(
    Chunk* const chunk,
    uint32_t const n_pieces,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(n_pieces > 0);
    assert(n_pieces <= AREA_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    return cutNEquallyN_chunk(chunk, n_pieces, LEN_CHUNK(chunk) - n, n);
}

Item cutNEquallyN_chunk(
    Chunk* const chunk,
    uint32_t const n_pieces,
    uint32_t const id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(n_pieces > 0);
    assert(n_pieces <= AREA_CHUNK(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - id);
    if (n_pieces == 1) return getN_chunk(chunk, id, n);

    for (uint32_t i = 1; i <= n; i++) {
        Item const orig_item    = get_chunk(chunk, id + n - i);
        uint32_t const sz_piece = orig_item.sz / n_pieces;
        assert(orig_item.sz % n_pieces == 0);

        insertIndeterminateN_alist(chunk->offsets, id + n - i + 1, n_pieces - 1);
        for (uint32_t j = id + n - i + 1, shft = sz_piece; j < id + n - i + n_pieces; j++, shft += sz_piece) {
            uint32_t const new_offset = orig_item.offset + shft;
            set_alist(chunk->offsets, j, &new_offset);
        }
    }

    return getN_chunk(chunk, id, n * n_pieces);
}

Item cutByDelimLastN_chunk(
    Chunk* const chunk,
    char const delim[],
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(delim != NULL);
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    return cutByDelimN_chunk(chunk, delim, LEN_CHUNK(chunk) - n, n);
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

void (* const deleteAll_chunk)(Chunk* const chunk) = &flush_chunk;

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

void flush_chunk(Chunk* const chunk) {
    assert(isValid_chunk(chunk));
    flush_alist(chunk->offsets);
    flush_alist(chunk->items);
}

Item getLastN_chunk(
    Chunk const* const chunk,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    return getN_chunk(chunk, LEN_CHUNK(chunk) - n, n);
}

Item getN_chunk(
    Chunk const* const chunk,
    uint32_t const id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - id);
    {
        Item item   = NOT_AN_ITEM;
        item.offset = offsetOf_chunk(chunk, id);
        item.sz     = area_chunk(chunk, id);
        item.p      = get_alist(chunk->items, item.offset);
        return item;
    }
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
    return mergeN_chunk(chunk, LEN_CHUNK(chunk) - n, n);
}

Item mergeN_chunk(Chunk* const chunk, uint32_t const first_id, uint32_t const n) {
    assert(isValid_chunk(chunk));
    assert(first_id < LEN_CHUNK(chunk));
    assert(n >= 2);
    assert(first_id + n <= LEN_CHUNK(chunk));
    deleteN_alist(chunk->offsets, first_id + 1, n - 1);
    return get_chunk(chunk, first_id);
}

uint32_t offsetOf_chunk(
    Chunk const* const chunk,
    uint32_t const id
) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    return *(uint32_t*)get_alist(chunk->offsets, id);
}

Item setAll_chunk(
    Chunk* const chunk,
    void const* const p_item,
    uint32_t const sz_item
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX);
    assert(p_item == NULL || !overlaps_ptr(chunk->items->array, p_item, AREA_CHUNK(chunk), sz_item));

    /* UB if chunk->items->array and p_item overlap. */
    return setLastN_chunk(chunk, p_item, sz_item, LEN_CHUNK(chunk));
}

Item setDupN_chunk(
    Chunk* const chunk,
    uint32_t const dup_id,
    uint32_t const orig_id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(dup_id < LEN_CHUNK(chunk));
    assert(orig_id < LEN_CHUNK(chunk));
    assert(dup_id != orig_id);
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - dup_id);
    assert(n <= LEN_CHUNK(chunk) - orig_id);
    {
        uint32_t const sz_orig  = areaBtw_chunk(chunk, orig_id, orig_id + n);
        uint32_t const sz_dup   = areaBtw_chunk(chunk, dup_id, dup_id + n);
        if (sz_dup > sz_orig)
            shrink_chunk(chunk, dup_id, sz_dup - sz_orig);
        else if (sz_dup < sz_orig)
            enlarge_chunk(chunk, dup_id, sz_orig - sz_dup);

        for (
            uint32_t i = dup_id + 1, j = orig_id, new_offset = offsetOf_chunk(chunk, dup_id) + area_chunk(chunk, j);
            i < dup_id + n;
            ++i, new_offset += area_chunk(chunk, ++j);
        ) set_alist(chunk->offsets, i, &new_offset);

        {
            uint32_t const off_orig = offsetOf_chunk(chunk, orig_id);
            uint32_t const off_dup  = offsetOf_chunk(chunk, dup_id);
            setDupN_alist(chunk->items, off_dup, off_orig, sz_orig);
        }
    }
    return getN_chunk(chunk, dup_id, n);
}

Item setDupSameN_chunk(
    Chunk* const chunk,
    uint32_t const dup_id,
    uint32_t const orig_id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(dup_id < LEN_CHUNK(chunk));
    assert(orig_id < LEN_CHUNK(chunk));
    assert(dup_id != orig_id);
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - dup_id);
    {
        uint32_t const off_orig = offsetOf_chunk(chunk, orig_id);
        uint32_t const off_dup  = offsetOf_chunk(chunk, dup_id);
        uint32_t const sz_orig  = area_chunk(chunk, orig_id);
        uint32_t const sz_total = areaBtw_chunk(chunk, dup_id, dup_id + n);
        uint32_t const sz_new   = sz_orig * n;
        assert(sz_new < SZ32_MAX);
        assert(sz_new / sz_orig == n);

        if (sz_total > sz_new) {
            if (orig_id == dup_id + n - 1)
                shrink_chunk(chunk, orig_id - 1, sz_total - sz_new);
            else
                shrink_chunk(chunk, dup_id + n - 1, sz_total - sz_new);
        } else if (sz_total < sz_new) {
            if (orig_id == dup_id + n - 1)
                enlarge_chunk(chunk, orig_id - 1, sz_new - sz_total);
            else
                enlarge_chunk(chunk, dup_id + n - 1, sz_new - sz_total);
        }

        for (uint32_t i = dup_id, new_offset = off_dup; i < dup_id + n; i++, new_offset += sz_orig)
            set_alist(chunk->offsets, i, &new_offset);

        {
            uint32_t sz = sz_orig;
            setDupN_alist(chunk->items, dup_off, orig_off, sz);
            while (sz << 1 < sz_new) {
                setDupN_alist(chunk->items, dup_off + sz, dup_off, sz);
                sz <<= 1;
            }
            if (sz_new > sz)
                setDupN_alist(chunk->items, dup_off + sz, dup_off, sz_new - sz);
        }
    }
    return getN_chunk(chunk, dup_id, n);
}

Item setLastN_chunk(
    Chunk* const chunk,
    void const* const p_item,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX);
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    assert(p_item == NULL || !overlaps_ptr(chunk->items->array, p_item, AREA_CHUNK(chunk), sz_item));

    deleteLastN_chunk(chunk, n);

    /* UB if chunk->items->array and p_item overlap. */
    return addN_chunk(chunk, p_item, sz_item, n);
}

Item setN_chunk(
    Chunk* const chunk,
    uint32_t const id,
    void const* const p_item,
    uint32_t const sz_item,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX);
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - id);
    assert(p_item == NULL || !overlaps_ptr(chunk->items->array, p_item, AREA_CHUNK(chunk), sz_item));
    {
        uint32_t const offset   = offsetOf_chunk(chunk, id);
        uint32_t const sz_total = arewBtw_chunk(chunk, id, id + n);
        uint32_t const sz_new   = sz_item * n;
        assert(sz_new < SZ32_MAX);
        assert(sz_new / sz_item == n);

        if (sz_total > sz_new)
            shrink_chunk(chunk, id + n - 1, sz_total - sz_new);
        else if (sz_total < sz_new)
            enlarge_chunk(chunk, id + n - 1, sz_new - sz_total);

        for (uint32_t i = id, new_offset = offset; i < id + n; i++, offset += sz_item)
            set_alist(chunk->offsets, i, &new_offset);

        {
            uint32_t sz = sz_item;
            set_alist(chunk->items, offset, p_item, sz);
            while (sz << 1 < sz_new) {
                setDupN_alist(chunk->items, offset + sz, offset, sz);
                sz <<= 1;
            }
            if (sz_new > sz)
                setDupN_alist(chunk->items, offset + sz, offset, sz_new - sz);
        }
    }

    return getN_chunk(chunk, id, n);
}

Item setZerosN_chunk(
    Chunk* const chunk,
    uint32_t const id,
    uint32_t const n
) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk) - id);
    {
        Item const first_item   = getN_chunk(chunk, id, n);
        uint32_t const sz_total = areaBtw_chunk(chunk, id, id + n);
        setZerosN_alist(chunk->items, first_item.offset, sz_total);
        return first_item;
    }
}

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
    assert(n <= LEN_CHUNK(chunk) - id1);
    assert(n <= LEN_CHUNK(chunk) - id0);
    for (uint32_t i = id0, j = id1; i < id0 + n; i++, j++) {
        addDup_chunk(chunk, i);
        setDup_chunk(chunk, i, j);
        setDup_chunk(chunk, j, LEN_CHUNK(chunk) - 1);
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
