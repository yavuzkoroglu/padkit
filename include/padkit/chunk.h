#ifndef PADKIT_CHUNK_H
    #define PADKIT_CHUNK_H
    #include "padkit/arraylist.h"

    #define AREA_CHUNK(chunk)   (chunk[0].size)
    #define LEN_CHUNK(chunk)    (chunk[1].size)

    #define NOT_A_CHUNK         { NOT_AN_ALIST, NOT_AN_ALIST }

    typedef ArrayList Chunk[2];

    void* addIndeterminateItem_chunk(ArrayList chunk[static const 2], uint32_t const sz);

    void* addItem_chunk(ArrayList chunk[static const 2], uint32_t const sz, void const* const restrict ptr);

    void* append_chunk(ArrayList chunk[static const 2], uint32_t const sz, void const* const restrict ptr);

    void* appendDuplicate_chunk(ArrayList chunk[static const 2], uint32_t const id);

    void concat_chunk(ArrayList head[static const restrict 2], ArrayList tail[static const restrict 2]);

    void constructEmpty_chunk(
        ArrayList chunk[static const 2],
        uint32_t const initial_cap_area,
        uint32_t const initial_cap_len
    );

    void delete_chunk(ArrayList chunk[static const 2], uint32_t const startId, uint32_t const n);

    void deleteLast_chunk(ArrayList chunk[static const 2], uint32_t const n);

    void* duplicateItem_chunk(ArrayList chunk[static const 2], uint32_t const id);

    void flush_chunk(ArrayList chunk[static const 2]);

    void free_chunk(ArrayList chunk[static const 2]);

    uint32_t fromStream_chunk(
        ArrayList chunk[static const 2], FILE stream[static const 1],
        char const delimeters[], size_t nDelimeters
    );

    uint32_t fromStreamAsWhole_chunk(ArrayList chunk[static const 2], FILE stream[static const 1]);

    void* get_chunk(ArrayList const chunk[static const 2], uint32_t const id);

    void* getLast_chunk(ArrayList const chunk[static const 2]);

    bool isValid_chunk(ArrayList const chunk[static const 2]);

    uint32_t splitLast_chunk(ArrayList chunk[static const 2], char const delimeters[], size_t nDelimeters);

    uint32_t sz_item_chunk(ArrayList const chunk[static const 2], uint32_t const id);

    uint32_t sz_itemLast_chunk(ArrayList const chunk[static const 2]);
#endif
