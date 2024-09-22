#ifndef PADKIT_CHUNK_H
    #define PADKIT_CHUNK_H
    #include "padkit/arraylist.h"
    #include "padkit/item.h"

    #define CHUNK_RECOMMENDED_PARAMETERS    ALIST_RECOMMENDED_INITIAL_CAP, ALIST_RECOMMENDED_INITIAL_CAP

    #define AREA_CHUNK(chunk)               (chunk[0].len)
    #define LEN_CHUNK(chunk)                (chunk[1].len)

    #define NOT_A_CHUNK                     { NOT_AN_ALIST, NOT_AN_ALIST }

    typedef ArrayList Chunk[2];

    void* addIndeterminate_chunk(
        ArrayList chunk[static const 2],
        uint32_t const sz
    );

    void* addItem_chunk(
        ArrayList chunk[static const 2],
        void const* const p,
        uint32_t const sz
    );

    void* append_chunk(
        ArrayList chunk[static const 2],
        void const* const p,
        uint32_t const sz
    );

    Item appendDuplicate_chunk(
        ArrayList chunk[static const 2],
        uint32_t const i
    );

    void concat_chunk(
        ArrayList head[static const 2],
        ArrayList tail[static const 2]
    );

    void constructEmpty_chunk(
        ArrayList chunk[static const 2],
        uint32_t const initial_cap_area,
        uint32_t const initial_cap_len
    );

    void deleteFirst_chunk(ArrayList chunk[static const 2], uint32_t const n);

    void deleteItem_chunk(ArrayList chunk[static const 2], uint32_t const id, uint32_t const n);

    void deleteLast_chunk(ArrayList chunk[static const 2], uint32_t const n);

    void* duplicateItem_chunk(ArrayList chunk[static const 2], uint32_t const id);

    void* duplicateItemLast_chunk(ArrayList chunk[static const 2]);

    void* enlargeItem_chunk(ArrayList chunk[static const 2], uint32_t const id, uint32_t const by);

    void* enlargeItemLast_chunk(ArrayList chunk[static const 2], uint32_t const by);

    void flush_chunk(ArrayList chunk[static const 2]);

    void free_chunk(ArrayList chunk[static const 2]);

    uint32_t fromStream_chunk(
        ArrayList chunk[static const 2], FILE stream[static const 1],
        char const delimeters[], size_t nDelimeters
    );

    void* fromStreamAsWhole_chunk(ArrayList chunk[static const 2], FILE stream[static const 1]);

    void* get_chunk(ArrayList const chunk[static const 2], uint32_t const id);

    void* getLast_chunk(ArrayList const chunk[static const 2]);

    bool isValid_chunk(ArrayList const chunk[static const 2]);

    void* resizeItem_chunk(ArrayList chunk[static const 2], uint32_t const id, uint32_t const sz_new);

    void* resizeItemLast_chunk(ArrayList chunk[static const 2], uint32_t const sz_new);

    void* setItem_chunk(
        ArrayList chunk[static const 2], uint32_t const id,
        uint32_t const sz, void const* const ptr
    );

    void* setItemLast_chunk(ArrayList chunk[static const 2], uint32_t const sz, void const* const ptr);

    void* shrinkItem_chunk(ArrayList chunk[static const 2], uint32_t const id, uint32_t const by);

    void* shrinkItemLast_chunk(ArrayList chunk[static const 2], uint32_t const by);

    uint32_t splitLast_chunk(ArrayList chunk[static const 2], char const delimeters[], size_t nDelimeters);

    uint32_t sz_item_chunk(ArrayList const chunk[static const 2], uint32_t const id);

    uint32_t sz_itemLast_chunk(ArrayList const chunk[static const 2]);
#endif
