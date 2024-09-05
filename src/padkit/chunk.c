#include <assert.h>
#include "padkit/chunk.h"
#include "padkit/size.h"

uint32_t add_chunk(ArrayList chunk[static const 2], uint32_t const sz, void const* const restrict ptr) {
    assert(isValid_chunk(chunk));
    assert(sz > 0);
    assert(sz < SZ32_MAX);

    add_alist(chunk, sz, ptr);
    add_alist(chunk + 1, 1, &(chunk[0][0].size));

    return chunk[1].size;
}

uint32_t addIndeterminate_chunk(ArrayList chunk[static const 2], uint32_t const sz) {
    assert(isValid_chunk(chunk));
    assert(sz > 0);
    assert(sz < SZ32_MAX);

    return add_chunk(chunk, sz, NULL);
}

uint32_t addIndex_chunk(ArrayList chunk[static const 2], uint32_t const id) {
    assert(isValid_chunk(chunk));
    assert(id < chunk[1].size);

    {
        void const* const element   = get_chunk(chunk, id);
        uint32_t const sz           = sz_chunk(chunk, id);
        uint32_t const new_id       = addIndeterminate_chunk(chunk, sz);

        set_alist(chunk[0], new_id, sz, element);

        return new_id;
    }
}

void const* append_chunk(ArrayList chunk[static const 2], )

void const* get_chunk(ArrayList chunk[static const 2], uint32_t const id) {
    assert(isValid_chunk(chunk));
    assert(id < chunk[1].size);

    return get_alist(chunk, get_alist(chunk + 1, id));
}

uint32_t sz_chunk(ArrayList chunk[static const 2], uint32_t const id) {
    assert(isValid_chunk(chunk));
    assert(id < chunk[1].size);

    if (id == chunk[1].size - 1) {
        uint32_t const* const offset = getLast_alist(chunk + 1);
        assert(chunk[0].size >= offset[0]);

        return chunk[0].size - offset[0];
    } else {
        uint32_t const* const offsets[2] = {
            get_alist(chunk + 1, id),
            get_alist(chunk + 1, id + 1),
        };
        assert(offsets[1][0] >= offsets[0][0]);

        return offsets[1][0] - offsets[0][0];
    }
}
