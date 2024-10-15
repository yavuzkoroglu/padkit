#ifndef PADKIT_CHUNK_H
    #define PADKIT_CHUNK_H
    #include <stdarg.h>
    #include "padkit/arraylist.h"
    #include "padkit/item.h"

    #define CHUNK_RECOMMENDED_PARAMETERS                    \
        ALIST_RECOMMENDED_INITIAL_CAP,                      \
        ALIST_RECOMMENDED_INITIAL_CAP

    #define LEN_CHUNK(chunk)                                (chunk->offsets->len)
    #define AREA_CHUNK(chunk)                               (chunk->items->len)

    #define NOT_A_CHUNK                                     (Chunk){ NOT_AN_ALIST, NOT_AN_ALIST }

    typedef struct ChunkBody {
        ArrayList offsets[1];
        ArrayList items[1];
    } Chunk;

    Item add_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item
    );

    #define addDup_chunk(chunk, id)                         addDupN_chunk(chunk, id, 1)

    Item addDupN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const n
    );

    #define addIndeterminate_chunk(chunk, sz_item)          addIndeterminateN_chunk(chunk, 1, sz_item)

    Item addIndeterminateN_chunk(
        Chunk* const chunk,
        uint32_t const n,
        uint32_t const sz_item
    );

    Item addZeros_chunk(
        Chunk* const chunk,
        uint32_t const sz_item
    );

    Item addZerosN_chunk(
        Chunk* const chunk,
        uint32_t const n,
        uint32_t const sz_item
    );

    Item appendDupLast_chunk(
        Chunk* const chunk,
        uint32_t const id
    );

    #define appendIndeterminateLast_chunk(chunk, sz_item)   appendLast_chunk(chunk, NULL, sz_item)

    Item appendLast_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item
    );

    void appendZerosLast_chunk(
        Chunk* const chunk,
        uint32_t const sz_item
    );

    void construct_chunk(void* const p_chunk, ...);

    void constructEmpty_chunk(
        Chunk* const chunk,
        uint32_t const init_cap_len,
        uint32_t const init_cap_area
    );

    void destruct_chunk(void* const p_chunk);

    Item divideEquallyLast_chunk(
        Chunk* const chunk,
        uint32_t const n
    );

    Item get_chunk(
        Chunk const* const chunk,
        uint32_t const id
    );

    #define getFirst_chunk(chunk)                           get_chunk(chunk, 0)

    Item getLast_chunk(Chunk const* const chunk);

    bool isAllocated_chunk(void const* const p_chunk);

    bool isValid_chunk(void const* const p_chunk);

    void vconstruct_chunk(
        void* const p_chunk,
        va_list args
    );
#endif
