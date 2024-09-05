#include <assert.h>
#include <string.h>
#include "padkit/chunk.h"
#include "padkit/invalid.h"
#include "padkit/size.h"

static char const defaultDelimeters[] = {' ', '\t', '\n', '\v', '\f', '\r', '\0'};

uint32_t addItem_chunk(ArrayList chunk[static const 2], uint32_t const sz, void const* const restrict ptr) {
    assert(isValid_chunk(chunk));
    assert(sz > 0);
    assert(sz < SZ32_MAX);

    add_alist(chunk + 1, 1, &AREA_CHUNK(chunk));
    add_alist(chunk, sz, ptr);

    return LEN_CHUNK(chunk) - 1;
}

uint32_t addIndeterminateItem_chunk(ArrayList chunk[static const 2], uint32_t const sz) {
    assert(isValid_chunk(chunk));
    assert(sz > 0);
    assert(sz < SZ32_MAX);

    return addItem_chunk(chunk, sz, NULL);
}

uint32_t duplicateItem_chunk(ArrayList chunk[static const 2], uint32_t const id) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    {
        uint32_t const sz_item  = sz_item_chunk(chunk, id);
        uint32_t const new_id   = addIndeterminateItem_chunk(chunk, sz_item);
        void const* const item  = get_chunk(chunk, id);

        set_alist(chunk, new_id, sz_item, item);

        return new_id;
    }
}

void* append_chunk(ArrayList chunk[static const 2], uint32_t const sz, void const* const restrict ptr) {
    assert(isValid_chunk(chunk));
    assert(sz > 0);
    assert(sz < SZ32_MAX);

    if (LEN_CHUNK(chunk) == 0)
        addItem_chunk(chunk, sz, ptr);
    else
        add_alist(chunk, sz, ptr);

    return getLast_chunk(chunk);
}

void* appendDuplicate_chunk(ArrayList chunk[static const 2], uint32_t const id) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));
    {
        uint32_t const sz_item = sz_item_chunk(chunk, id);
        uint32_t const startId = AREA_CHUNK(chunk);
        addIndeterminate_alist(chunk, sz_item);
        {
            void* const item = get_chunk(chunk, id);
            set_alist(chunk, startId, sz_item, item);
        }
    }

    return getLast_chunk(chunk);
}

void concat_chunk(ArrayList head[static const 2], ArrayList tail[static const 2]) {
    uint32_t const head_area = AREA_CHUNK(head);

    assert(isValid_chunk(head));
    assert(isValid_chunk(tail));

    concat_alist(head, tail);

    for (uint32_t i = 0; i < LEN_CHUNK(tail); i++) {
        uint32_t const* const old_offset    = get_alist(tail + 1, i);
        uint32_t const new_offset           = head_area + *old_offset;
        add_alist(head + 1, 1, &new_offset);
    }
}

void constructEmpty_chunk(
    ArrayList chunk[static const 2],
    uint32_t const initial_cap_area,
    uint32_t const initial_cap_len
) {
    assert(initial_cap_area > 0);
    assert(initial_cap_area < SZ32_MAX);
    assert(initial_cap_len > 0);
    assert(initial_cap_len < SZ32_MAX);

    constructEmpty_alist(chunk, 1, initial_cap_area);
    constructEmpty_alist(chunk + 1, sizeof(uint32_t), initial_cap_len);
}

void delete_chunk(ArrayList chunk[static const 2], uint32_t const startId, uint32_t const n) {
    assert(isValid_chunk(chunk));
    assert(startId < LEN_CHUNK(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));
    assert(startId + n <= LEN_CHUNK(chunk));

    if (startId + n == LEN_CHUNK(chunk)) {
        deleteLast_chunk(chunk, n);
    } else {
        uint32_t const* const offsets[2] = {
            get_alist(chunk + 1, startId),
            get_alist(chunk + 1, startId + n)
        };
        uint32_t const len = offsets[1][0] - offsets[0][0];
        assert(len < AREA_CHUNK(chunk));

        delete_alist(chunk, offsets[0][0], len);
        delete_alist(chunk + 1, startId, n);
        for (uint32_t i = startId; i < LEN_CHUNK(chunk); i++) {
            uint32_t* const offset = get_alist(chunk + 1, i);
            assert(*offset > len);
            *offset -= len;
        }
    }
}

void deleteLast_chunk(ArrayList chunk[static const 2], uint32_t const n) {
    assert(isValid_chunk(chunk));
    assert(n > 0);
    assert(n <= LEN_CHUNK(chunk));

    if (n == LEN_CHUNK(chunk)) {
        flush_chunk(chunk);
    } else {
        uint32_t const* const offset = get_alist(chunk + 1, LEN_CHUNK(chunk) - n);
        assert(AREA_CHUNK(chunk) >= *offset);

        removeLast_alist(chunk, AREA_CHUNK(chunk) - *offset);
        removeLast_alist(chunk + 1, n);
    }
}

void flush_chunk(ArrayList chunk[static const 2]) {
    assert(isValid_chunk(chunk));

    flush_alist(chunk);
    flush_alist(chunk + 1);
}

void free_chunk(ArrayList chunk[static const 2]) {
    assert(isValid_chunk(chunk));

    free_alist(chunk);
    free_alist(chunk + 1);
}

uint32_t fromStream_chunk(
    ArrayList chunk[static const 2], FILE stream[static const 1],
    char const delimeters[], size_t nDelimeters
) {
    assert(isValid_chunk(chunk));
    {
        uint32_t id = fromStreamAsWhole_chunk(chunk, stream);
        if (splitLast_chunk(chunk, delimeters, nDelimeters) == 0)
            return INVALID_UINT32;
        else
            return id;
    }
}

uint32_t fromStreamAsWhole_chunk(ArrayList chunk[static const 2], FILE stream[static const 1]) {
    assert(isValid_chunk(chunk));

    if (fseek(stream, 0L, SEEK_END) != 0) {
        return INVALID_UINT32;
    } else {
        long const size = ftell(stream);
        if (size < 0L) {
            return INVALID_UINT32;
        #if ULONG_MAX >= UINT32_MAX
            } else if ((unsigned long)size >= SZ32_MAX) {
                return INVALID_UINT32;
        #endif
        #if ULONG_MAX >= SIZE_MAX
            } else if ((unsigned long)size >= SZSZ_MAX) {
                return INVALID_UINT32;
        #endif
        } else if (fseek(stream, 0L, SEEK_SET) != 0) {
            return INVALID_UINT32;
        } else {
            uint32_t const id   = addIndeterminateItem_chunk(chunk, (uint32_t)size);
            void* const dest    = get_chunk(chunk, id);
            if (fread(dest, (size_t)size, 1, stream) == 1)
                return id;
            else
                return INVALID_UINT32;
        }
    }
}

void* get_chunk(ArrayList const chunk[static const 2], uint32_t const id) {
    assert(isValid_chunk(chunk));
    assert(id < LEN_CHUNK(chunk));

    return get_alist(chunk, *(uint32_t*)get_alist(chunk + 1, id));
}

void* getLast_chunk(ArrayList const chunk[static const 2]) {
    assert(isValid_chunk(chunk));
    assert(LEN_CHUNK(chunk) > 0);

    return get_chunk(chunk, LEN_CHUNK(chunk) - 1);
}

bool isValid_chunk(ArrayList const chunk[static const 2]) {
    if (!isValid_alist(chunk))                  return 0;
    if (!isValid_alist(chunk + 1))              return 0;
    if (LEN_CHUNK(chunk) > AREA_CHUNK(chunk))   return 0;

    return 1;
}

uint32_t splitLast_chunk(ArrayList chunk[static const 2], char const delimeters[], size_t nDelimeters) {
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

        LEN_CHUNK(chunk) = *old_offset + i;

        if (i == 0) {
            n--;
            removeLast_alist(chunk + 1, 1);
        }

        return n;
    }
}

uint32_t sz_item_chunk(ArrayList const chunk[static const 2], uint32_t const id) {
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

uint32_t sz_itemLast_chunk(ArrayList const chunk[static const 2]) {
    assert(isValid_chunk(chunk));
    {
        uint32_t const* const offset = getLast_alist(chunk + 1);
        assert(AREA_CHUNK(chunk) >= *offset);

        return AREA_CHUNK(chunk) - *offset;
    }
}
